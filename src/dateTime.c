#include "Write2Display.h" 
#include "getkey.h"
//-------------USED TO CONFIUGRE TIME WITH KEYPAD------------------
 unsigned int s = 55;
 unsigned int m = 30;//tens + ones
 unsigned int h = 20;

 unsigned int mFLAG = 0;
 unsigned int hFLAG = 0;
 void calcTime();
//----------------------------------------------------------------
 
 
//-------------USED TO CONFIUGRE TIME WITH KEYPAD------------------
 

 unsigned int day = 12;
 unsigned int month = 4;
 unsigned int year = 99;
 unsigned int dayFLAG = 0;
 unsigned int monthFLAG = 0;
 unsigned int yearFLAG = 0;
 void calcDate();
 void printDate();
 void printTime();
 
 
 int printFLAG = 0;
 
//----------------------------------------------------------------
 
 //---------------------------------- BELOW IS FOR SETTING DATE-----------------------------------------
 
 
 
 void setDay()
 {
  
  
  if(printFLAG == 1) //print only once
  {
     clearDisplay();
     printLetter('D');
     printLetter('D');
     printLetter('=');
     printFLAG++;
  }
  
 if(func() != 0)
 {
  if (dayFLAG== 1)
  {
    if (func() == 11)
    {
      day = 0;
      PrintNum(0);
    }
    else
    {
      PrintNum(func());
      day = 10*func();
    }
    dayFLAG = 2;  
    Delay(15000000);
  }

    else if (dayFLAG == 2)
    {
      if (func() == 11)
      {        
        day += 0;
        PrintNum(0);
      }
      else 
      {
        day += func();
        PrintNum(func());
      }
      dayFLAG = 0;
      monthFLAG = 1;
      Delay(15000000);
    }
  }
} 


void setMonth()
 {
  
  if(printFLAG == 2)
  {
     clearDisplay();
     printLetter('M');
     printLetter('M');
     
     printLetter('=');
     printFLAG++;
  }
 if(func() != 0)
 {
  if (monthFLAG== 1)
  {
    if (func() == 11)
    {
      PrintNum(0);
      month = 0;
    }
    else
    {
      month = 10*func();
      PrintNum(func());
    }
    monthFLAG = 2;  
    Delay(15000000);
  }

    else if (monthFLAG == 2)
    {
      if (func() == 11)
      {
        PrintNum(0);
        month += 0;
      }
      else 
      {
        PrintNum(func());
        month += func();
      }
      monthFLAG = 0;
      yearFLAG = 1;
      Delay(15000000);
    }
  }
} 
 
void setYear()
 {
 
  if(printFLAG ==3)
  {
     clearDisplay();
     printLetter('Y');
     printLetter('Y');
     
     
     printLetter('=');
     printFLAG = 0;
  }
 if(func() != 0)
 {
  if (yearFLAG== 1)
  {
    if (func() == 11)
    {
      PrintNum(0);
      year = 0;
    }
    else
    {
      PrintNum(func());
      year = 10*func();
    }
    yearFLAG = 2;  
    Delay(15000000);
  }

    else if (yearFLAG == 2)
    {
      if (func() == 11)
      {
        PrintNum(0);
        year += 0;
      }
      else 
      {
        PrintNum(func());
        year += func();
      }
      yearFLAG = 0;
      printDate();
      Delay(15000000);
    }
  }
} 


 void setDate(void)
{
  dayFLAG = 1;
  printFLAG = 1;
  clearDisplay();
  return;
}

void goDate()
 {
  if (dayFLAG)
    setDay();
  if(monthFLAG)
    setMonth();
  if(yearFLAG)
    setYear();
 }
 
 void printDate()
 {
  clearDisplay();
   //print YY/MM/DD =
     
  printLetter('Y');
  printLetter('Y');
  
  printLetter('/');
  
  printLetter('M');
  printLetter('M');
  
  printLetter('/');
  
  printLetter('D');
  printLetter('D');
  
  printLetter('=');
 
  PrintNum(year/10);
  PrintNum((year%10)/1);
    
  printLetter('/');
   
  PrintNum(month/10);
  PrintNum((month%10)/1);
    
  printLetter('/');
   
  PrintNum(day/10);
  PrintNum((day%10)/1);
    
  
 }

//-------------------------------------------------------------------------------------------------------------


//---------------------------------- ALL BELOW IS FOR SETTING TIME-----------------------------------------
void goTime()
 {
  if (mFLAG)
   setM();
  if(hFLAG)
    setH();
 }
 
void setTime(void)
{
  mFLAG = 1;
  printFLAG = 1;
  clearDisplay();
  return;
}

void setM(void)
{
  

  if(printFLAG ==1)
  {
    clearDisplay();
    Write_Data_2_Display(0x4D);// m
    Write_Command_2_Display(0xC0);//
    Write_Data_2_Display(0x4D);// m
    Write_Command_2_Display(0xC0);//
     
    printLetter('=');
    printFLAG++;
  }
 if(func() != 0)
 {
  // skriv på skärmen: m =
  if (mFLAG== 1)
  {
    if (func() == 11)
    {
      PrintNum(0); 
      m = 0;
    }
    else
    {
      m = 10*func();
      PrintNum(func());
    }
    mFLAG = 2;  
    Delay(15000000);
  }

    else if (mFLAG == 2)
    {
      if (func() == 11)
      {
        PrintNum(0);
        m += 0;
      }
      else 
      {
        PrintNum(func());
        m += func();
      }
      mFLAG = 0;
      hFLAG = 1;
      Delay(15000000);
    }
  }
} 


void setH(void)
{
  
 
  if(printFLAG ==2)
  {
  // skriv på skärmen: h =
      clearDisplay();
      Write_Data_2_Display(0x48);// h
      Write_Command_2_Display(0xC0);//
      Write_Data_2_Display(0x48);// h
      Write_Command_2_Display(0xC0);//
     
     printLetter('=');
     printFLAG = 0;
  }
  
  if (func()!= 0)
  {
    if(hFLAG == 1)
    {
      if (func() == 11)//if input a 0
      {
        h = 0;
        PrintNum(0);
      }
      else
      {
        PrintNum(func());
        h = 10*func();
      }
        hFLAG = 2;    
        Delay(15000000);
    }
    else if (hFLAG ==2)
    {
      if(func() == 11)//if input a 0
      {
        PrintNum(0);
        h += 0;
      }
      else
      {
        PrintNum(func());
        h += func();
      }
      s = 0;
      hFLAG = 0;
      printTime();
      Delay(15000000);
    }
  }
}



void printTime()
 {
   
   //print hh:mm:ss =
  clearDisplay();
  Write_Data_2_Display(0x48);   // h
  Write_Command_2_Display(0xC0);//
  Write_Data_2_Display(0x48);   // h
  Write_Command_2_Display(0xC0);//
  
  printLetter(':');
  
  Write_Data_2_Display(0x4D);   // m
  Write_Command_2_Display(0xC0);//
  Write_Data_2_Display(0x4D);   // m
  Write_Command_2_Display(0xC0);//
  
  printLetter(':');
  
  Write_Data_2_Display(0x53);   // s
  Write_Command_2_Display(0xC0);//
  Write_Data_2_Display(0x53);   // s
  Write_Command_2_Display(0xC0);//
  
  printLetter('=');
 
  PrintNum(h/10);
  PrintNum((h%10)/1);
    
  printLetter(':');
   
  PrintNum(m/10);
  PrintNum((m%10)/1);
    
  printLetter(':');
   
  PrintNum(s/10);
  PrintNum((s%10)/1);
    
  
 }
  void printDateTime()
  {
    clearDisplay();
    printDate();
    for (int i = 0; i <23;i++)
    {
      printLetter(' ');
    }
    printTime();
  }
//-------------------------------------------------------------------------------------------------------------



int getDaysInMonth(unsigned int month)
{
  unsigned int daysInMonth = 0;
  switch (month)
  {
  case 1:
    daysInMonth = 31;
    break;
  case 2:
    daysInMonth = 28;
    break;
  case 3:
    daysInMonth = 31;
    break;
  case 4:
    daysInMonth = 30;
    break;
  case 5:
    daysInMonth = 31;
    break;
  case 6:
    daysInMonth = 30;
    break;
  case 7:
    daysInMonth = 31;
    break;
  case 8:
    daysInMonth = 31;
    break;
  case 9:
    daysInMonth = 30;
    break;
  case 10:
    daysInMonth = 31;
    break;
  case 11:
    daysInMonth = 30;
    break;
  case 12:
    daysInMonth = 31;
    break;
  }
  return daysInMonth;
  
}

