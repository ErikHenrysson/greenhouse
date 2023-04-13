#include "system_sam3x.h"
#include "at91sam3x8.h"

void configLed(void)
{
*AT91C_PIOD_PER =(1<<3); //Activate pin 28 (LED)
*AT91C_PIOD_PPUDR =(1<<3); //Disable pull up register
*AT91C_PIOD_OER =(1<<3); //enable pin as output
 *AT91C_PIOD_CODR =(1<<3);//turn of at start
}

void setLed(unsigned int onoff)
{
  if (onoff == 1)
    *AT91C_PIOD_SODR =(1<<3);
  else 
    *AT91C_PIOD_CODR =(1<<3);
}