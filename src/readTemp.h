#ifndef readTemp_h
#define readTemp_h
#include "LinkedList.h"
int getTemp(void);
void configTemp();
void setMinMaxTemp();
void startTemp();
void Delay(int Value);
void Systick_Handler(void);
void resetTemp();
void TC0_Handler(void);
void goTemp(struct LinkedList** first);
void checkAlarm();
void printWarning(unsigned int hotCold);
void configMaxMinTemp();
void configMinTemp();
void configMaxTemp();
void configMinMaxAvgList();
void printMinMaxAvg();

extern int delay;
extern int reset;
extern int TCFLAG;
extern int startFLAG;
extern int id;
extern unsigned int temp;
extern unsigned int maxTemp;
extern int minTemp;
extern unsigned int minFLAG;
extern unsigned int maxFLAG;
extern unsigned int printMinMaxFLAG;
extern unsigned int daysPassed;


#endif