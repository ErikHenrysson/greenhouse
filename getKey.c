#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "Write2Display.h"
#include "getKey.h"
#include "dateTime.h"
#include "printTemp.h"
#include "structs.h"
#include "readTemp.h"

void printMenu(void);
void deactivateSpeedMode(); 
void activateSpeedMode();
unsigned int speedFLAG = 0;
void getFunc(unsigned int pressedKey,struct LinkedList* first)
{
if (pressedKey == 0)//do nothing if idle
{
  return;
}
else if (pressedKey == 1 && speedFLAG == 0) //use this to set date
{
  setDate();
  Delay(15000000);
}
else if (pressedKey == 2 && speedFLAG == 0)//use this to set time
{
  setTime();
  Delay(15000000);
}
else if (pressedKey == 3 && speedFLAG == 0)
{
  printDateTime();
}
else if (pressedKey == 4)
{
  printMinMaxAvg();
  //printMinMaxAvg(first);
}
else if (pressedKey == 5)
{
 
}
else if (pressedKey == 6 && speedFLAG == 0)
{
  //SET UPPER AND LOWER TEMP LIMIT FOR ALARM
  setMinMaxTemp();
  Delay(15000000);
}
else if (pressedKey == 7)
{
  activateSpeedMode();
}
else if (pressedKey == 8)
{
  deactivateSpeedMode();
}
else if (pressedKey == 9)
{

}
else if (pressedKey == 10)
{

}
else if (pressedKey == 11)
{
 clearDisplay();
 printMenu();
}
else if (pressedKey == 12)
{

}
  //Delay(15000000);
}

  void activateSpeedMode()
  {
    speedFLAG = 1;
  }
  void deactivateSpeedMode()
  {
    speedFLAG = 0;
  }


int func(void){

  int value = 0;
  
  // Enable Keypad, Disable Display
  *AT91C_PIOC_SODR=(1<<12);       //Display Gate
  *AT91C_PIOD_CODR=(1<<2);        //Keypad Gate
  
  *AT91C_PIOC_OER = (1<<8); //Set Column pin as output
  *AT91C_PIOC_OER = (1<<9); //Set Column pin as output    
  *AT91C_PIOC_OER = (1<<7); //Set Column pin as output 

  for(int i =1; i<4; i++)
  {
  *AT91C_PIOC_SODR = (1<<8); //col 1
  *AT91C_PIOC_SODR = (1<<9); //col 2
  *AT91C_PIOC_SODR = (1<<7); //col 3
  *AT91C_PIOC_CODR = (1<<(i+6));
  
  // i = 7 col 3, i = 8 col 1, i = 9 col 2
  // row 2, row 3, row 4, row 1
  /* ROW ORDER:
 j = 5 row 1
 j = 2 row 2
 j = 3 row 3
 j = 4 row 4

*/
    for (int j = 1; j < 5; j++)
    {
        if ((*AT91C_PIOC_PDSR&(1<<(j+1)))==(0<<1))
        {
                    value = j*3 +i+1;
                    break;
        }
    }
  }
  
  *AT91C_PIOC_ODR = (1<<8);//enable the pin as an input (set output DISABLE register)
  *AT91C_PIOC_ODR = (1<<9);//enable the pin as an input (set output DISABLE register)
  *AT91C_PIOC_ODR = (1<<7);//enable the pin as an input (set output DISABLE register)
  
  *AT91C_PIOD_SODR=(1<<2);        //Keypad Gate
  *AT91C_PIOC_CODR=(1<<12);       //Display Gate
  if(value == 0)
  {
    return value;
  }

  else if (value == 15)
  {
    return value = 1;
  }
  else if (value == 16)
  {
    return value = 2;
  }
  else if (value == 14)
  {
    return value = 3;
  }
  else if (value == 6)
  {
    return value = 4;
  }
  else if (value == 7)
  {
    return value = 5;
  }
  else if (value == 5)
  {
    return value = 6;
  }
  else if (value == 9)
  {
    return value = 7;
  }
  else if (value == 10)
  {
    return value = 8;
  }
  else if (value == 8)
  {
    return value = 9;
  }
  else if (value == 12)
  {
   return value = 10;//STJÄRNA!
  }
  else if (value == 13)
  {
    return value = 11;
  }
  else if (value == 11)
  {
    return value = 12; //fyrkant
  }
    // Disable Keypad, Enable Display

  return 0;
}

void configKeyPad(void)
{
    /*
            ///////////////  Keypad only Pins  \\\\\\\\\\\\\\\\\\\\\\\
  */
  *AT91C_PMC_PCER = (1<<14); //Enable PIOD
  *AT91C_PMC_PCER = (1<<13); //Enable PIOC
  
  //Pin 27 (PD 2) (G, Gate) Active Low
  *AT91C_PIOD_PER = (1<<2);
  *AT91C_PIOD_OER = (1<<2);
  
  //Pin 34 (PC 2) (DB0)
  *AT91C_PIOC_PER = (1<<2);
  *AT91C_PIOC_PPUDR = (1<<2);
  
  //Pin 35 (PC 3) (DB1)
  *AT91C_PIOC_PER = (1<<3);
  *AT91C_PIOC_PPUDR = (1<<3);
  
  //Pin 36 (PC 4) (DB2)
  *AT91C_PIOC_PER = (1<<4);
  *AT91C_PIOC_PPUDR = (1<<4);
  
  //Pin 37 (PC 5) (DB3)
  *AT91C_PIOC_PER = (1<<5);
  *AT91C_PIOC_PPUDR = (1<<5);
  
  //Pin 39 (PC 7) (DB5)
  *AT91C_PIOC_PER = (1<<7);
  *AT91C_PIOC_PPUDR = (1<<7);
  
  //Pin 40 (PC 8) (DB6)
  *AT91C_PIOC_PER = (1<<8);
  *AT91C_PIOC_PPUDR = (1<<8);
  
  //Pin 41 (PC 9) (DB7)
  *AT91C_PIOC_PER = (1<<9);
  *AT91C_PIOC_PPUDR = (1<<9);
}

void printMenu(void)
{
/*THIS WILL PRINT 

1. SET DATE 

2. SET TIME 

3. SHOW DATE & TIME 

4. Show recorded data max min and avarge

6. Configure min and maxtemp

7. Activate speedmode

8. deactivate speedmode

*/ 
  /* ----------------------ROW BEFORE OPTIONS---------------------- */
  printLetter('M');
  printLetter('E');
  printLetter('N');
  printLetter('U');
  
 
  for (int i = 0; i <36;i++)
    {
      printLetter(' ');
    }
   /* -------------------------------------------------------------- */
  
  
   /* ----------------------------ROW 1----------------------------- */
  PrintNum(1);
  printLetter('.');
  printLetter(' ');
  printLetter('S');
  printLetter('E');
  printLetter('T');
  printLetter(' ');
  printLetter('D');
  printLetter('A');
  printLetter('T');
  printLetter('E');
  
  for (int i = 0; i <29;i++)
    {
      printLetter(' ');
    }
  /* -------------------------------------------------------------- */
  
  
  /* ----------------------------ROW 2----------------------------- */
  PrintNum(2);
  printLetter('.');
  printLetter(' ');
  printLetter('S');
  printLetter('E');
  printLetter('T');
  printLetter(' ');
  printLetter('T');
  printLetter('I');
  printLetter('M');
  printLetter('E');
  for (int i = 0; i <29;i++)
    {
      printLetter(' ');
    }
  /* -------------------------------------------------------------- */
  
  
  /* ----------------------------ROW 3----------------------------- */
  /*PrintNum(3);
  printLetter('.');
  printLetter(' ');
  printLetter('S');
  printLetter('H');
  printLetter('O');
  printLetter('W');
  printLetter(' ');
  printLetter('D');
  printLetter('A');
  printLetter('T');
  printLetter('E');
  printLetter(' ');
  printLetter('&');
  printLetter(' ');
  printLetter('T');
  printLetter('I');
  printLetter('M');
  printLetter('E');
  
    for (int i = 0; i <21;i++)
    {
      Write_Data_2_Display(0x00);// print " " to make it to other row
      Write_Command_2_Display(0xC0);//
    }
*/
  /* -------------------------------------------------------------- */
    
    
  /* ----------------------------ROW 4----------------------------- */
  PrintNum(4);
  printLetter('.');
  printLetter(' ');
  printLetter('P');
  printLetter('R');
  printLetter('I');
  printLetter('N');
  printLetter('T');
  printLetter(' ');
  printLetter('M');
  printLetter('I');
  printLetter('N');
  printLetter(' ');
  printLetter('M');
  printLetter('A');
  printLetter('X');
  printLetter(' ');
  printLetter('A');
  printLetter('V');
  printLetter('G');
  
  for (int i = 0; i <20;i++)
    {
      printLetter(' ');
    }
  /* -------------------------------------------------------------- */  
  
  
  /* ----------------------------ROW 5----------------------------- */
  /* -------------------------------------------------------------- */
  
  
  /* ----------------------------ROW 6----------------------------- */
  PrintNum(6);
  printLetter('.');
  printLetter(' ');
  printLetter('C');
  printLetter('O');
  printLetter('N');
  printLetter('F');
  printLetter('I');
  printLetter('G');
  printLetter(' ');
  printLetter('M');
  printLetter('I');
  printLetter('N');
  printLetter(' ');
  printLetter('M');
  printLetter('A');
  printLetter('X');
  printLetter(' ');
  printLetter('T');
  printLetter('E');
  printLetter('M');
  printLetter('P');
  
  for (int i = 0; i <18;i++)
    {
      printLetter(' ');
    }
  /* -------------------------------------------------------------- */
  
  
  /* ----------------------------ROW 7----------------------------- */
  PrintNum(7);
  printLetter('.');
  printLetter(' ');
  printLetter('A');
  printLetter('C');
  printLetter('T');
  printLetter('I');
  printLetter('V');
  printLetter('A');
  printLetter('T');
  printLetter('E');
  printLetter(' ');
  printLetter('S');
  printLetter('P');
  printLetter('E');
  printLetter('E');
  printLetter('D');
  printLetter('M');
  printLetter('O');
  printLetter('D');
  printLetter('E');
  
  for (int i = 0; i <19;i++)
    {
      printLetter(' ');
    }
  /* -------------------------------------------------------------- */
  
  
  /* ----------------------------ROW 8----------------------------- */
  PrintNum(8);
  printLetter('.');
  printLetter(' ');
  printLetter('D');
  printLetter('E');
  printLetter('A');
  printLetter('C');
  printLetter('T');
  printLetter('I');
  printLetter('V');
  printLetter('A');
  printLetter('T');
  printLetter('E');
  printLetter(' ');
  printLetter('S');
  printLetter('P');
  printLetter('E');
  printLetter('E');
  printLetter('D');
  printLetter('M');
  printLetter('O');
  printLetter('D');
  printLetter('E');
  /* -------------------------------------------------------------- */
  
  
  /* ----------------------------ROW 9----------------------------- */
  /* -------------------------------------------------------------- */
  
}
