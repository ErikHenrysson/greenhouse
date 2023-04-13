#include "system_sam3x.h"
#include "at91sam3x8.h"
#include <stdio.h>
#include <stdlib.h>
#include "readTemp.h"
#include "readLight.h"
#include "servo.h"
#include "Write2Display.h"
#include "structs.h"
#include "LinkedList.h"
#include "getKey.h"
#include "dateTime.h"
#include "printTemp.h"
#include "led.h"
#include "readLight.h"

int isIdle();
struct LinkedList** first;
struct LinkedList* Node;
unsigned int timeCounter = 0;

void updateTime();
void updateScreen();


int main()
{
  SystemInit();
  first = (struct LinkedList**)malloc(1*sizeof(struct LinkedList));
  *first = NULL;
  if (first == 0)
  printf("Out of memory!\n");
  configTemp();
  configDisp();
  configKeyPad();
  Init_Display();
  clearDisplay();
  configLed();
  configLight();
  configMinMaxAvgList();
  
  InitServo();

  while(1)
  {
    goTime();
    goDate();
    goLight();
    goServo();
    configMaxMinTemp();
    updateTime();
    goTemp(first);
    if (isIdle()) //if no function is running
    {
    getFunc(func(),*first);
    updateScreen();
    }
    
    if (daysPassed >= 7)//mätningen klar
      break;
  }  

return 1;
}

int isIdle()
{
if((mFLAG == 0) && (hFLAG == 0)&&(dayFLAG == 0)&&(monthFLAG == 0)&&(yearFLAG == 0)&&(minFLAG ==0)&&(maxFLAG ==0)&&(TCFLAG == 0)&&(startFLAG == 0))
  return 1;

  return 0;
}

void SysTick_Handler(void)
{
    //for keeping time
    timeCounter++;
    
    if(speedFLAG == 1) //speedmode, activated by pressing 7, deactiavated by pressing 8
    {
      if (timeCounter%50 == 0)
      {
        timeCounter%=50;
        s = 60;
      } 
    }
    else if (speedFLAG == 0) //normal mode, standard
    {
      if(timeCounter%1000 == 0) //1000 ms = 1 s
      {
        timeCounter%=1000;
        s++;
      }
    }
  
    //for the temp reading:
  
    if (delay == 15)
    {
      reset = 0;
      delay = 0;
    }
    if (reset == 1)
    {
      delay++;
    }
}

void updateTime()
{
    if(s == 60) //60 s = 1 m
    {
      //starta templäsningen!
      startFLAG = 2;
      lightFLAG++;
      s = 0;
      m++;
    }
    if (m == 60) //60 min = 1 h
    {
      m=0;
      h++;
    }
    if (h == 24)//if you reach midnight, add 1 to day
    {
      //print max min and avarage temp
     // printMinMaxAvg(first);
      daysPassed++;
      h =0;
      day++;
    }
    if (day ==getDaysInMonth(month))   //if it goes over 30 days, add to month (maybe swithc with the different months?)
    {
      day = 1;
      month++;
    }
    if(month==13) //if the month becomes january, add a year
     {
       month =1;
       year++;
     }


}
void updateScreen()
{
    setCursorPointer(13,26);
    printLetter('T');
    printLetter('E');
    printLetter('M');
    printLetter('P');
    printLetter(':');
    printLetter(' ');
    PrintNum(temp/10);
    PrintNum((temp%10)/1);
    printLetter('C');
  
  
    setCursorPointer(14,26);
    printLetter('T');
    printLetter('I');
    printLetter('M');
    printLetter('E');
    printLetter(':');
    printLetter(' ');
    PrintNum(h/10);
    PrintNum((h%10)/1);
    printLetter(':');
    
    PrintNum(m/10);
    PrintNum((m%10)/1);
    printLetter(':');
    
    PrintNum(s/10);
    PrintNum((s%10)/1);

    
    setCursorPointer(15,26);
    
    printLetter('D');
    printLetter('A');
    printLetter('T');
    printLetter('E');
    printLetter(':');
    printLetter(' ');
    PrintNum(year/10);
    PrintNum((year%10)/1);
    printLetter(':');
    
    PrintNum(month/10);
    PrintNum((month%10)/1);
    printLetter(':');
    
    PrintNum(day/10);
    PrintNum((day%10)/1);

}
