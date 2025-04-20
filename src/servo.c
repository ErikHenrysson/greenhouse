#include "at91sam3x8.h"
#include "system_sam3x.h"
#include "getKey.h"
#include "dateTime.h"

void InitServo()
{
  *AT91C_PIOB_PDR=(1<<17);      // Let peripheral control the pin A
  
  *AT91C_PIOB_ABMR=(1<<17);     // Activate peripheral B to control  the pin in  REG_PIOB_ABSR == 1
  
  *AT91C_PMC_PCER1 = (1<<4);     // Enable PMC for PWM controller
  
  *AT91C_PWMC_WPCR=(0<<2);      // Clear bit at register group 0
  
  *AT91C_PWMC_ENA = (1<<1);
  
  *AT91C_PWMC_WPCR=(0<<4);      // Clear bit at register group 2
  //*AT91C_PWMC_WPCR=(0<<10);     // clears the correct bits ti make the next line work in register
  
  AT91C_BASE_PWMC_CH1->PWMC_CMR =(0x5);// (0b0101) Set Pre-scaler to Master_CLK/32 
  
  *AT91C_PWMC_WPCR=(0<<5);              // Clear bit at register group 3
  //*AT91C_PWMC_WPCR=(0<<11);             // Clears bits  WPSWP43 and WPHWS3
  
  *AT91C_PWMC_CH1_CPRDR=(52500);        // Write a value to PWM_CPRD (20ms)
  
  *AT91C_PWMC_WPCR=(0<<6);              // Clear bit at register group 4
  //*AT91C_PWMC_WPCR=(0<<12);             // Clears bits  WPSWP4 and WPHWS4
  
  AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 2625;    // 1ms
  AT91C_BASE_PWMC->PWMC_UPCR = 0x1;             // Update the duty cycle
  
  // *AT91C_PWMC_CH1_DTUPDR=();            // Write a value to PWM_CDTY (2625);
}

void setServo(unsigned int pressedKey)
{
  // Set PWM Duty Cycle depending on the pressed button
  switch (pressedKey) {
  case 1:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 2070; // 2070 for 10  degrees
    break;
  case 2:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 2304; // 2304 for 20  degrees
    break;
  case 3:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 2538; // 2537   for 30  degrees
    break;
  case 4:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 2771; // 2770 40  degrees
    break;
  case 5:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 3004; // 3004 50  degrees
    break;
  case 6:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 3238; // 3237 60  degrees
    break;
  case 7:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 3471; // 3470 70  degrees
    break;
  case 8:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 3704; // 3704 80  degrees
    break;
  case 9:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 3937; // 3937 90  degrees
    break;
  case 10:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 4170; // 4170 100 degrees
    break;
  case 11:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 4404; // 4404 110 degrees
    break;
  case 12:
    AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 4637; // 4637 120 degrees
    break;
  case 0:
     AT91C_BASE_PWMC_CH1->PWMC_CDTYUPDR = 1750; //neutral 0 degrees
     break;
  }  
  
  
  
}
void goServo()
  {
  if (h<8)
    setServo(12);
  else
    setServo(0);
  }