#include "system_sam3x.h"
#include "at91sam3x8.h"

void Write_Data_2_Display(unsigned char Data);
void Write_Command_2_Display(unsigned char Data);

void Delay(int Value){
  int i;
  for(i=0;i<Value;i++)
  asm("nop");
}

void setCursor(void)
{
    Write_Data_2_Display(0x00);// y = 0 x = 0
    Write_Data_2_Display(0x00);// y = 0 x = 0
    //Write_Command_2_Display(0x21);// set cursor pointer
    Write_Command_2_Display(0x24);  
}
void clearDisplay(void)
{
//40 col 16 rows
  setCursor();
  for (int i = 0; i < (16*40); i++)
  {
    Write_Data_2_Display(0x0);// blank space
    Write_Command_2_Display(0xC0);// write and increment
  }
  setCursor();
}

void setCursorPointer(int row, int col)
{
  int data = 40*row + col;
  char lower = (char)data;
  data = (data>>8);
  char upper = (char)data;
  
  Write_Data_2_Display(lower);// y = 0 x = 0
  Write_Data_2_Display(upper);// y = 0 x = 0
  //Write_Command_2_Display(0x21);// set cursor pointer
  Write_Command_2_Display(0x24);
  
  
}


void configDisp()
{
 *AT91C_PMC_PCER = (1<<14); //Enable PIOD
  *AT91C_PMC_PCER = (1<<13); //Enable PIOC
  
 //Pin 38(PC 6) (DB 4) Only Data pin that does not share with keypad
  *AT91C_PIOC_PER = (1<<6);
  *AT91C_PIOC_PPUDR = (1<<6);

  
  //Pin 44 (PC 19) (RV, Reverse Display )
  *AT91C_PIOC_PER = (1<<19);
  *AT91C_PIOC_OER = (1<<19);
  *AT91C_PIOC_CODR = (1<<19);

    
  //Pin 45 (PC 18) (FS, Font Select )
  *AT91C_PIOC_PER = (1<<18);
  *AT91C_PIOC_OER = (1<<18);
  *AT91C_PIOC_SODR = (1<<18);
 
  
  //Pin 46 (PC 17) (WR, Write Register)
  *AT91C_PIOC_PER = (1<<17);
  *AT91C_PIOC_OER = (1<<17); 

  
  //Pin 47 (PC 16) (RD, Read Register)
  *AT91C_PIOC_PER = (1<<16);
  *AT91C_PIOC_OER = (1<<16);

  
  //48 (PC 15) (CE, Chip Enable) 
  *AT91C_PIOC_PER = (1<<15);
  *AT91C_PIOC_OER = (1<<15);

  
  //Pin 49 (PC 14) (C/D, Command and Data) 
  *AT91C_PIOC_PER = (1<<14);
  *AT91C_PIOC_OER = (1<<14);
  
  //Pin 50 (PC 13) (DIR, Direction) 
  *AT91C_PIOC_PER = (1<<13);
  *AT91C_PIOC_OER = (1<<13);
  
  //Pin 51 (PC 12) (G, Gate) 
  *AT91C_PIOC_PER = (1<<12);
  *AT91C_PIOC_OER = (1<<12);
  
  /*
        /////////////  Shared DataPins, Display and Keypad \\\\\\\\\\\\\\\\\
  */
  
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
  *AT91C_PIOC_PPUDR = (1<<9);}

void SetDBInput(){ //Sets the databus pins to input
  //PIN 34 to B8 on chip - Aktiverad av keypad 
  *AT91C_PIOC_ODR = (1<<2); //enable the pin as an input
  //PIN 35 to B7 on chip - Aktiverad av keypad
  *AT91C_PIOC_ODR = (1<<3); //enable the pin as an input
  //PIN 36 to B6 on chip - Aktiverad av keypad
  *AT91C_PIOC_ODR = (1<<4); //enable the pin as an input
  //PIN 37 to B5 on chip - Aktiverad av keypad
  *AT91C_PIOC_ODR = (1<<5); //enable the pin as an input
  //PIN 38 to B4 on chip
  *AT91C_PIOC_ODR = (1<<6); //enable the pin as an input
  //PIN 39 to B3 on chip - Aktiverad av keypad
  *AT91C_PIOC_ODR = (1<<7); //enable the pin as an input
  //PIN 40 to B2 on chip - Aktiverad av keypad
  *AT91C_PIOC_ODR = (1<<8); //enable the pin as an input
  //PIN 41 to B1 on chip - Aktiverad av keypad
  *AT91C_PIOC_ODR = (1<<9); //enable the pin as an input
  
  //*AT91C_PIOC_ODR = 0xF1FE; //enable the pins as an input
}

void SetDBOutput(){ //Sets the databus pins to output
  //PIN 34 to B8 on chip - Aktiverad av keypad 
  *AT91C_PIOC_OER = (1<<2); //enable the pin as an output
  //PIN 35 to B7 on chip - Aktiverad av keypad
  *AT91C_PIOC_OER = (1<<3); //enable the pin as an output
  //PIN 36 to B6 on chip - Aktiverad av keypad
  *AT91C_PIOC_OER = (1<<4); //enable the pin as an output
  //PIN 37 to B5 on chip - Aktiverad av keypad
  *AT91C_PIOC_OER = (1<<5); //enable the pin as an output
  //PIN 38 to B4 on chip
  *AT91C_PIOC_OER = (1<<6); //enable the pin as an output
  //PIN 39 to B3 on chip - Aktiverad av keypad
  *AT91C_PIOC_OER = (1<<7); //enable the pin as an output
  //PIN 40 to B2 on chip - Aktiverad av keypad
  *AT91C_PIOC_OER = (1<<8); //enable the pin as an output
  //PIN 41 to B1 on chip - Aktiverad av keypad
  *AT91C_PIOC_OER = (1<<9); //enable the pin as an output
}


void clearDB(){//Clears databus
   //PIN 34 to B8 on chip - Aktiverad av keypad 
  *AT91C_PIOC_CODR = (1<<2); //enable the pin as an output
  //PIN 35 to B7 on chip - Aktiverad av keypad
  *AT91C_PIOC_CODR = (1<<3); //enable the pin as an output
  //PIN 36 to B6 on chip - Aktiverad av keypad
  *AT91C_PIOC_CODR = (1<<4); //enable the pin as an output
  //PIN 37 to B5 on chip - Aktiverad av keypad
  *AT91C_PIOC_CODR = (1<<5); //enable the pin as an output
  //PIN 38 to B4 on chip
  *AT91C_PIOC_CODR = (1<<6); //enable the pin as an output
  //PIN 39 to B3 on chip - Aktiverad av keypad
  *AT91C_PIOC_CODR = (1<<7); //enable the pin as an output
  //PIN 40 to B2 on chip - Aktiverad av keypad
  *AT91C_PIOC_CODR = (1<<8); //enable the pin as an output
  //PIN 41 to B1 on chip - Aktiverad av keypad
  *AT91C_PIOC_CODR = (1<<9); //enable the pin as an output
}


unsigned char Read_Status_Display(void)
{
  
  unsigned char Temp;
  
  //Make databus as input  
  SetDBInput();

  // Set dir as input (74chip, 1 = input) 
  *AT91C_PIOC_SODR=(1<<13);
  
  // Clear/enable output (74chip 0 = enable)
  *AT91C_PIOC_CODR = (1<<12);
  
  // Set C/D
  *AT91C_PIOC_SODR=(1<<14);
  
  // Clear chip select display
  *AT91C_PIOC_CODR = (1<<15);
  
  // Clear read display
  *AT91C_PIOC_CODR = (1<<16);
  
  // Set write display high 
  *AT91C_PIOC_SODR = (1<<17);
  
  // Make a Delay
  Delay(10);
  
  // Read data bus and save it in temp pc 2 -> pc 9, bit shift right so we can fit in a 8 bit char
  Temp = ((*AT91C_PIOC_PDSR & 0x3FC) >> 2);
  
  // Set chip select display
  *AT91C_PIOC_SODR = (1<<15);
  
  // Set read display
  *AT91C_PIOC_SODR = (1<<16);
  
  // Disable output (74chip)
  *AT91C_PIOC_SODR = (1<<12);
  
  // Set dir as output (74chip) 
  *AT91C_PIOC_CODR = (1<<13);
  
  return Temp;
  
}

void Write_Command_2_Display(unsigned char Command)
{
  
  //Wait until Read_Status_Display returns an OK wait until bit 0 (SD1) and 1 (SD0) is 1,
  while (!((Read_Status_Display()) & 0x03 == 0x03) ){};
  
  //Clear databus
  clearDB();
  
  //Set Command to databus 
   *AT91C_PIOC_SODR = (((unsigned int)Command)<<2);
  
  
  //Set dir as output (74chip) 
  *AT91C_PIOC_CODR=(1<<13);
  
  //Enable output (74chip) 
  *AT91C_PIOC_CODR=(1<<12);
  
  //Set databus as output 
  SetDBOutput();
  // Set C/D signal High (1 = Command)
  *AT91C_PIOC_SODR=(1<<14);
  
  // Clear chip select display
  *AT91C_PIOC_CODR = (1<<15);
  
  // Clear write display
  *AT91C_PIOC_CODR = (1<<17);
  
  // Make a Delay
  Delay(10);
  
  // Set chip enable display
  *AT91C_PIOC_SODR=(1<<15);
  
  // Set write display
  *AT91C_PIOC_SODR=(1<<17);
  
  // Disable output (74chip)
  *AT91C_PIOC_SODR=(1<<14);
  
  //Make databus as input  
  SetDBInput();
  
}


void PrintNum(unsigned char num)
{
  unsigned char upper = 0x10;
  unsigned char lower = 0;
  unsigned char displayChar = 0;
  // Convert keypad number to 
  if(num == 1)
  {
    lower = 0x01;
  }
  else if(num == 2)
    lower = 0x02;
  else if (num == 3)
    lower = 0x03;
  else if (num ==4)
    lower = 0x04;
  else if (num ==5)
    lower = 0x05;
  else if (num ==6)
    lower = 0x06;
  else if (num ==7)
    lower = 0x07;
  else if (num==8)
    lower = 0x08;
  else if (num ==9)
    lower = 0x09;
  else if (num == 10)
  {  
    lower = 0x0A;
    upper = 0;
  }
  else if (num==11)
    lower = 0;
  else if (num ==12)
  {
    lower = 0x03;
    upper = 0;
  }

  // Fuse the high and the low bits of the font table
  displayChar = upper | lower;
  
  // Write data to display
  Write_Data_2_Display(displayChar);
  
  Write_Command_2_Display(0xC0);
  
}

void Write_Data_2_Display(unsigned char Data)
{
  //Wait until Read_Status_Display returns an OK wait until bit 0 (SD1) and 1 (SD0) is 1,
  while (!((Read_Status_Display()) & 0x03 == 0x03) ){};
  
  //Clear databus
  clearDB();
  
  //Set Command to databus 
  *AT91C_PIOC_SODR = (((unsigned int)Data)<<2);
  
  
  //Set dir as output (74chip) 
  *AT91C_PIOC_CODR=(1<<13);
  
  //Enable output (74chip) 
  *AT91C_PIOC_CODR=(1<<12);
  
  //Set databus as output 
  SetDBOutput();
  
  // Clear C/D signal High (0 = Data)
  *AT91C_PIOC_CODR=(1<<14);
  
  // Clear chip select display
  *AT91C_PIOC_CODR = (1<<15);
  
  // Clear write display
  *AT91C_PIOC_CODR = (1<<17);
  
  // Make a Delay
  Delay(10);
  
  // Set chip enable display
  *AT91C_PIOC_SODR=(1<<15);
  
  // Set write display
  *AT91C_PIOC_SODR=(1<<17);
  
  // Disable output (74chip)
  *AT91C_PIOC_SODR=(1<<14);
  
  //Make databus as input    
  SetDBInput();
  
}
void Init_Display(void)
{
  // Clear Reset display
  *AT91C_PIOD_CODR = (1<<0);
  
  // Make a delay
  Delay(10);
  
  // Set Reset display
  *AT91C_PIOD_SODR = (1<<0);
  
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40); // Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x40);
  Write_Command_2_Display(0x42); // Set graphic home address
  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x41); // Set text area
  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43); // Set graphic area
  Write_Command_2_Display(0x80); // text mode
  Write_Command_2_Display(0x94); // Text on graphic off
}
  

void ActivateLCD(){
  *AT91C_PIOD_SODR = (1<<2);//Turn off keypadchip PIN 27
  *AT91C_PIOC_CODR =(1<<12); //Turn on LCDchip PIN 51
}


void printLetter(char letter) 
{ 
unsigned char upper = 0x0; 
unsigned char lower = 0x0; 
unsigned char displaychar = 0x0; 

switch (letter){ 
case 'A': 
upper = 0x20; 
lower = 0x1; 
break; 
case 'B': 
upper = 0x20; 
lower = 0x2; 
break; 
case 'C': 
upper = 0x20; 
lower = 0x3; 
break; 
case 'D': 
upper = 0x20; 
lower = 0x4; 
break; 
case 'E': 
upper = 0x20; 
lower = 0x5; 
break; 
case 'F': 
upper = 0x20; 
lower = 0x6; 
break; 
case 'G': 
upper = 0x20; 
lower = 0x7; 
break; 
case 'H': 
upper = 0x20; 
lower = 0x8; 
break; 
case 'I': 
upper = 0x20; 
lower = 0x9; 
break; 
case 'J': 
upper = 0x20; 
lower = 0xA; 
break; 
case 'K': 
upper = 0x20; 
lower = 0xB; 
break; 
case 'L': 
upper = 0x20; 
lower = 0xC; 
break; 
case 'M': 
upper = 0x20; 
lower = 0xD; 
break; 
case 'N': 
upper = 0x20; 
lower = 0xE; 
break; 
case 'O': 
upper = 0x20; 
lower = 0xF; 
break; 
case 'P': 
upper = 0x30; 
lower = 0x0; 
break; 
case 'Q': 
upper = 0x30; 
lower = 0x1; 
break; 
case 'R': 
upper = 0x30; 
lower = 0x2;
break; 
case 'S': 
upper = 0x30;
lower = 0x3;
break; 
case 'T': 
upper = 0x30; 
lower = 0x4;
break; 
case 'U': 
upper = 0x30; 
lower = 0x5; 
break; 
case 'V': 
upper = 0x30; 
lower = 0x6; 
break;
case 'W': 
upper = 0x30; 
lower = 0x7;
break; 
case 'X': 
upper = 0x30; 
lower = 0x8; 
break; 
case 'Y': 
upper = 0x30; 
lower = 0x9; 
break; 
case 'Z': 
upper = 0x30; 
lower = 0xA; 
break; 
case ' ': 
upper = 0x0; 
lower = 0x0; 
break; 
case '.': 
upper = 0x0; 
lower = 0xE; 
break; 
case '&': 
upper = 0x00; 
lower = 0x6; 
break; 
case ':':
upper = 0x10;
lower = 0xA;
break;
case'/':
upper = 0x0;
lower = 0xF;
break;
case '!':
upper =0x00;
lower = 0x1;
break;
case '=':
upper = 0x10;
lower=0xD;
break;
case ',':
upper=0x00;
lower =0x7;
break;
} 
  
displaychar = upper|lower; 
Write_Data_2_Display(displaychar);
Write_Command_2_Display(0xC0);
}
