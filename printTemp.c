#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Write2Display.h"
//set a temp day to the day of the first element in the lsit
//go through all the elements with the same day and get min max avg
//print and repeat
double getMax(struct LinkedList* first, int day);
double getMin(struct LinkedList* first, int day);
double getAvg(struct LinkedList* first, int day);
int getNextDay(struct LinkedList* first, int day);
int maxH = 0;
int maxM = 0;

int minH = 0;
int minM = 0;


/*
void printMinMaxAvg(struct LinkedList* first)
{
    clearDisplay();
    //set day to first elements day
    //send the list and that day to functions
    //increment day
    //stop when the day becomes 0
  
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
    
    
  int day = first->DD;
  while (day!= 0)//go through the whole list and check if date is same and if bigger/smaller
  {
    int maxTemp = (int)getMax(first, day);
    int minTemp = (int)getMin(first, day);
    int avgTemp = (int)getAvg(first, day);
    PrintNum(day/10);
    PrintNum((day%10)/1);
    
    for (int i = 0; i < 5; i++)
      printLetter(' ');
    
    PrintNum(minTemp/10); //prints the min number tens
    PrintNum((minTemp%10)/1);//ones
    printLetter('/');
    PrintNum(minH/10);
    PrintNum((minH%10)/1);
    printLetter(':');
    PrintNum(minM/10);
    PrintNum((minM%10)/1);
    
    for (int i = 0; i< 4;i++)
      printLetter(' ');
    
    PrintNum(maxTemp/10); //prints the max number tens
    PrintNum((maxTemp%10)/1);//ones
    printLetter('/');
    PrintNum(maxH/10);
    PrintNum((maxH%10)/1);
    printLetter(':');
    PrintNum(maxM/10);
    PrintNum((maxM%10)/1);
    
    
    for (int i = 0; i< 4;i++)
      printLetter(' ');
    
    
    
    PrintNum(avgTemp/10); //prints the avg number tens
    PrintNum((avgTemp%10)/1); //ones
    day = getNextDay(first, day);
    
    for (int i = 0; i< 7;i++)
      printLetter(' ');
  }
}
*/

int getNextDay(struct LinkedList* first, int day)
{
  struct LinkedList* temp = first;
  int nextDay = day;
  while (temp != NULL)
  {
    if ((temp->DD)>nextDay)
      return temp->DD;
    temp = temp->next;
  }
  
  return 0;
}

double getMax(struct LinkedList* first, int day) //gets the max value of a specifik day
{
  double max = first->sensorData;
  maxH= first->hh;
  maxM = first->mm;
  struct LinkedList* temp = first->next;
  while (temp!= NULL)
  {
    if ((max < temp->sensorData)&&(temp->DD==day))
    {
      max = temp->sensorData;
      maxH= temp->hh;
      maxM = temp->mm;
    }
    temp= temp->next;
  }
  return max;
}

double getMin(struct LinkedList* first, int day) //gets the max value of a specifik day
{
  
  double min = first->sensorData;
  minH = first->hh;
  minM= first->mm;
  struct LinkedList* temp = first->next;
  while (temp!=NULL)
  {
    if ((min > temp->sensorData)&&(temp->DD==day))
    {
      min = temp->sensorData;
      minH = temp->hh;
      minM= temp->mm;
    }
    temp= temp->next;
  }
  return min;
}

double getAvg(struct LinkedList* first, int day) //gets the max value of a specifik day
{
  double avg = 0;
  int count = 0;
  struct LinkedList* temp = first;
  while (temp!= NULL)
  {
    if (temp->DD==day)
    {
      avg+= temp->sensorData;
      count++;
    }
      temp= temp->next;
  }
  
  return avg/count;
}

void printTemp(int temperature)
{
  //TESTA DETTA MED KITTET:
  //Write_Data_2_Display(0x00);
  //Write_Command_2_Display(0x21);
  Write_Data_2_Display(0x5F);   // Make space for easier reading
  Write_Command_2_Display(0xC0);//
  
 unsigned char tens = temperature/10;
 temperature = temperature%10;
 
 unsigned char ones = temperature/1;
 
 PrintNum(tens);//
 PrintNum(ones);//
 
 Write_Data_2_Display(0x7);// degrees
 Write_Command_2_Display(0xC0);//
 
 Write_Data_2_Display(0x23);// celcius
 Write_Command_2_Display(0xC0);//
 
 Write_Data_2_Display(0x5F);   // Make space for easier reading
  Write_Command_2_Display(0xC0);//
}