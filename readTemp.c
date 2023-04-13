#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "Write2Display.h"
#include "LinkedList.h"
#include "structs.h"
#include "dateTime.h"
#include "getKey.h"
#include "printTemp.h"

/*kolla till 4:an!! */
void printMinMaxAvg();
void updateMinMaxAvgList(struct LinkedList* newEl);
void printWarning(unsigned int hotCold);
void checkAlarm();
void printMinMaxTemp();
unsigned int delay = 0;
unsigned int reset = 0;
unsigned int TCFLAG = 0;
unsigned int startFLAG = 0;
int temp = 0;
unsigned int maxTemp = 100;

int minTemp =-70;

unsigned int minFLAG = 0;
unsigned int maxFLAG = 0;

unsigned int printMinMaxFLAG = 0;

int id = 1;

unsigned int daysPassed = 0; //used for keeping the minmaxavg
struct minMaxAvgNode minMaxAvgList[7];

void TC0_Handler(void)
{  
  unsigned int state = *AT91C_TC0_SR ;
  if (( state &(1<<6))==(1<<6)) //if B has been loaded since last time checked
  TCFLAG = 1; //Set a global flag  
  
  *AT91C_TC0_IDR = (1<<6); //Disable interrupt for LDRBS 
}

int getTemp(void)
{
  int A =*AT91C_TC0_RA;
  int B = *AT91C_TC0_RB;
  int nCycles = B-A;
  double time = (nCycles/42); //
  int calcedTemp = (int)(time/5 -273.15);
  return calcedTemp;
}

void resetTemp()
{
  reset = 1;//starts systick
  *AT91C_PIOB_OER = (1<<25);//set pin as output 
  
  *AT91C_PIOB_CODR = (1<<25); //send 0 for 16 ms
  while(reset!=0){}

  *AT91C_PIOB_SODR = (1<<25);//set it back to 1 after 16 ms
}

void startTemp()
{
  resetTemp();
  *AT91C_PIOB_OER = (1<<25);//set pin as output 
  *AT91C_PIOB_CODR = (1<<25); //send 0 for 2.5 micros
  Delay(25);
  *AT91C_PIOB_SODR = (1<<25);//
  *AT91C_TC0_CCR = 0x4; //reset and clock is started
  *AT91C_TC0_SR; //read to clear old events


  *AT91C_PIOB_ODR = (1<<25); //set pin as input for reading
  *AT91C_TC0_IER = (1<<6);//Enable interrupt LDRBS
}

void configMinMaxAvgList()
{
  for(int i = 0; i<7; i++)
  {
    minMaxAvgList[i].antal = 0;
    minMaxAvgList[i].avarage = 0;
    minMaxAvgList[i].day = 0;
    minMaxAvgList[i].max = 0;
    minMaxAvgList[i].maxH = 0;
    minMaxAvgList[i].maxM = 0;
    minMaxAvgList[i].maxS = 0;
    minMaxAvgList[i].min = 0;
    minMaxAvgList[i].minH = 0;
    minMaxAvgList[i].minM = 0;
    minMaxAvgList[i].minS = 0;
  }
}

void configTemp()
{
  SysTick_Config(SystemCoreClock / 1000); //Enables Systick Clock
  //Enable the PIOs
   *AT91C_PMC_PCER = (1<<12)|(1<<27); //Enable PIOB
    *AT91C_TC0_CCR = 0x5; //reset and clock is started
   
   
   // The following pins are on* AT91C_PIOB_PER
   //bit 19 & 18 LDRB Rising edge bit 17 & 16 LDRA Falling Edge
   *AT91C_TC0_CMR=*AT91C_TC0_CMR&(0xFFF8); //selects timerclock1 aswell
   *AT91C_TC0_CMR=*AT91C_TC0_CMR|(0x6<<16);
   //Pin 2//PB25 (Digital pin 2) Thermal sensor
   *AT91C_PIOB_PER = (1<<25);//Enable pin 2
   *AT91C_PIOB_PPUDR = (1<<25); //Disable pull up resistor on pin 2
    resetTemp();
   
  NVIC_ClearPendingIRQ(TC0_IRQn);//TC0_IRQn = nr 27
  NVIC_SetPriority(TC0_IRQn,1);
  NVIC_EnableIRQ(TC0_IRQn);  
  *AT91C_TC0_SR;
}

void goTemp(struct LinkedList** first)
{
  if (startFLAG==2)
   {
     startTemp();
     startFLAG=1;
   }
   else if (TCFLAG == 1)
    {
      temp = getTemp();
      TCFLAG=0;
      struct LinkedList* tempNode = createTempNode(first, id, temp, year, month, day, h, m, s);
      insertLast(first, tempNode);
      updateMinMaxAvgList(tempNode);
      id ++;
      checkAlarm();
      startFLAG =0;
      //printList(*first); //slows down the programme very much
    }
}

void updateMinMaxAvgList(struct LinkedList* newEl)
{
  minMaxAvgList[daysPassed].antal++;
  minMaxAvgList[daysPassed].avarage+=newEl->sensorData;
  minMaxAvgList[daysPassed].day=newEl->DD;
  if ((newEl->sensorData)>minMaxAvgList[daysPassed].max)//if the new elements temp is hotter than max in array
  {
    minMaxAvgList[daysPassed].max=(int)newEl->sensorData;
    minMaxAvgList[daysPassed].maxH=newEl->hh;
    minMaxAvgList[daysPassed].maxM=newEl->mm;
    minMaxAvgList[daysPassed].maxS=newEl->ss;
  }
  if (((newEl->sensorData)<minMaxAvgList[daysPassed].min)||minMaxAvgList[daysPassed].min == 0)//if the new elements temp is colder than min in array
  {
    minMaxAvgList[daysPassed].min=(int)newEl->sensorData;
    minMaxAvgList[daysPassed].minH=newEl->hh;
    minMaxAvgList[daysPassed].minM=newEl->mm;
    minMaxAvgList[daysPassed].minS=newEl->ss;
  }  
}

void printMinMaxAvg()
{
  //printa minmaxavg listan! 
    clearDisplay();
  
    printLetter('D');
    printLetter('A');
    printLetter('Y');
    printLetter(' ');
    printLetter(' ');
    printLetter(' ');
    printLetter(' ');
    
    printLetter('M');
    printLetter('I');
    printLetter('N');
    printLetter('/');
    printLetter('T');
    printLetter('I');
    printLetter('M');
    printLetter('E');
    printLetter(' ');
    printLetter(' ');
    printLetter(' ');
    printLetter(' ');
    
    printLetter('M');
    printLetter('A');
    printLetter('X');
    printLetter('/');
    printLetter('T');
    printLetter('I');
    printLetter('M');
    printLetter('E');
    printLetter(' ');
    printLetter(' ');
    printLetter(' ');
    printLetter(' ');
    
    printLetter('A');
    printLetter('V');
    printLetter('G');
    for (int i = 0;i <6 ;i++)
      printLetter(' ');
    

  for (int i = 0; i< 7; i++)
  {
    PrintNum(minMaxAvgList[i].day/10);
    PrintNum((minMaxAvgList[i].day%10)/1);
  
    for (int i = 0; i < 5; i++)
      printLetter(' ');
    
    PrintNum(minMaxAvgList[i].min/10); //prints the min number tens
    PrintNum((minMaxAvgList[i].min%10)/1);//ones
    printLetter('/');
    PrintNum(minMaxAvgList[i].minH/10);
    PrintNum((minMaxAvgList[i].minH%10)/1);
    printLetter(':');
    PrintNum(minMaxAvgList[i].minM/10);
    PrintNum((minMaxAvgList[i].minM%10)/1);
  
    for (int i = 0; i< 4;i++)
      printLetter(' ');
    
    PrintNum(minMaxAvgList[i].max/10); //prints the max number tens
    PrintNum((minMaxAvgList[i].max%10)/1);//ones
    printLetter('/');
    PrintNum(minMaxAvgList[i].maxH/10);
    PrintNum((minMaxAvgList[i].maxH%10)/1);
    printLetter(':');
    PrintNum(minMaxAvgList[i].maxM/10);
    PrintNum((minMaxAvgList[i].maxM%10)/1);
    
    for (int i = 0; i< 4;i++)
      printLetter(' ');
    
    PrintNum((minMaxAvgList[i].avarage/minMaxAvgList[i].antal)/10); //prints the avg number tens
    PrintNum(((minMaxAvgList[i].avarage/minMaxAvgList[i].antal)%10)/1); //ones
    
    for (int i = 0; i< 7;i++)
      printLetter(' ');
  
  }
  
}

void checkAlarm()
{
  if(temp > maxTemp)
    printWarning(1);//1 -->> too hot
  if(temp < minTemp)
    printWarning(0);//0 -->> too cold
    
}


void printWarning(unsigned int hotCold)
{
  clearDisplay();
  
  if (hotCold == 1)
  {
    printLetter('T');
    printLetter('O');
    printLetter('O');
    
    printLetter(' ');
    
    printLetter('H');
    printLetter('O');
    printLetter('T');
    printLetter('!');
  }
  else if (hotCold == 0)
  {
    printLetter('T');
    printLetter('O');
    printLetter('O');
    
    printLetter(' ');
    
    printLetter('C');
    printLetter('O');
    printLetter('L');
    printLetter('D');
    printLetter('!');
  }
}



void configMinTemp()
{
  
 if(printMinMaxFLAG == 1) //print only once
  {
     clearDisplay();
     printLetter('M');
     printLetter('I');
     printLetter('N');
     printLetter(' ');
     printLetter('T');
     printLetter('E');
     printLetter('M');
     printLetter('P');
     printLetter(':');
     Delay(15000000);
     printMinMaxFLAG++;
  }
  
 if(func() != 0)
 {
  if (minFLAG== 1)
  {
    if (func() == 11)
      minTemp = 0;
    else
    minTemp = 10*func();
    minFLAG = 2;  
    Delay(15000000);
  }

    else if (minFLAG == 2)
    {
      if (func() == 11)
        minTemp += 0;
      else 
      minTemp += func();
      minFLAG = 0;
      maxFLAG = 1;
      Delay(15000000);
    }
  }

}

void configMaxTemp()
{
   if(printMinMaxFLAG == 2) //print only once
  {
     clearDisplay();
     printLetter('M');
     printLetter('A');
     printLetter('X');
     printLetter(' ');
     printLetter('T');
     printLetter('E');
     printLetter('M');
     printLetter('P');
     printLetter(':');
     printMinMaxFLAG= 0;
  }
  if(func() != 0)
 {
  if (maxFLAG== 1)
  {
    if (func() == 11)
      maxTemp = 0;
    else
    maxTemp = 10*func();
    maxFLAG = 2;  
    Delay(15000000);
  }

    else if (maxFLAG == 2)
    {
      if (func() == 11)
        maxTemp += 0;
      else 
      maxTemp += func();
      maxFLAG = 0;
      //calcMinMaxTemp();
      printMinMaxTemp();
      Delay(15000000);
    }
  }
  
}

void setMinMaxTemp()
{
  minFLAG = 1;
  printMinMaxFLAG = 1;
}
void configMaxMinTemp()
{
  if(minFLAG)
    configMinTemp();
  if(maxFLAG)
    configMaxTemp();
}

void printMinMaxTemp()
{
  clearDisplay();
  printLetter('M');
  printLetter('I');
  printLetter('N');
  printLetter(' ');
  printLetter('T');
  printLetter('E');
  printLetter('M');
  printLetter('P');
  printLetter(':');
  printLetter(' ');
  PrintNum(minTemp/10);
  PrintNum((minTemp%10)/1);
  printLetter('C');
  for (int i = 0; i< 27; i++)
  printLetter(' ');
  printLetter('M');
  printLetter('A');
  printLetter('X');
  printLetter(' ');
  printLetter('T');
  printLetter('E');
  printLetter('M');
  printLetter('P');
  printLetter(':');
  printLetter(' ');
  PrintNum(maxTemp/10);
  PrintNum((maxTemp%10)/1);
  printLetter('C');
}