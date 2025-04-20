#include "at91sam3x8.h"
#include "system_sam3x.h"
#include "Write2Display.h"
#include "led.h"
#include "dateTime.h"

int light1 = 0;
int light2 = 0;
int lightFLAG=0;
void startMeasurement();


//if the time is between 00:00 and 08:00, led should always be off
//if the time is between 08:00 and 00:00 the led should be on if the light is too low
void goLight()
{
    if(lightFLAG ==10)
    {
    lightFLAG = 0;
    startMeasurement();
    }
    
    
    if(((light1 > 800)||(light2 > 800))&&h>=8) 
    {
      setLed(1);
      return;
    }
    else
    {
      setLed(0);
    }
    
}

// Init ADC for LightSensor
void configLight()
{
  // Enable PMC for ADC
  //*AT91C_PMC_PCER = (1<<11);
  *AT91C_PMC_PCER1 = (1<<5); // Bit shift 5 for PID37
  *AT91C_ADCC_MR = (1<<10); // Set prescaler for ADC: 84MHz / 6 = 14MHz
  
  NVIC_ClearPendingIRQ(ADC_IRQn);
  NVIC_SetPriority(ADC_IRQn,1);
  NVIC_EnableIRQ(ADC_IRQn); 

  *AT91C_ADCC_IER = (1<<1)|(1<<2);

}

void ADC_Handler(void)
{
  
  //läser EOC 1 och 2, för att se om någon av dem kanalerna har gett ett värde
  unsigned int status = *AT91C_ADCC_SR;
  if ((status & (1<<1)) == (1<<1))
  {
    light1 = (int)((*AT91C_ADCC_CDR1*(3.3/4.096)));
  }
  
  if ((status & (1<<2)) == (1<<2))
  {
    light2 = (int)((*AT91C_ADCC_CDR2*(3.3/4.096)));
  }
}

// Start the ADC Measurement
void startMeasurement()
{
  *AT91C_ADCC_CHER = (1<<1)|(1<<2);    // Enable light sensor PIN59
  *AT91C_ADCC_CR = (1<<1); // Start analog-to-digital conversion
  
  // Wait until the data is ready / DRDY is 1
  while (~(*AT91C_ADCC_SR &(1<<24)) == (1<<24)){
  }
  //light1 = *AT91C_ADCC_LCDR;
}

void printVoltage()
{
  
   int ones = (int)((light1/1000));
   light1=light1%1000;
   int dec = (int)((light1/100));
   
  PrintNum(ones);
  
  
  printLetter(',');
   
  PrintNum(dec);
   
  printLetter('V');
  
  printLetter(' ');
  
   ones = (int)((light2/1000));
   light2=light2%1000;
   dec = (int)((light2/100));

  PrintNum(ones);
 
  
  printLetter(',');
   
  PrintNum(dec);
   
  printLetter('V');
  
  printLetter(' ');
   


}