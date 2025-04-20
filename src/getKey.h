#ifndef getKey
#define getKey
#include "structs.h"
extern unsigned int s;
extern unsigned int m;
extern unsigned int h;
extern unsigned int sFLAG;
extern unsigned int mFLAG;
extern unsigned int hFLAG;
extern unsigned int day;
extern unsigned int month;
extern unsigned int year;
extern unsigned int dayFLAG;
extern unsigned int speedFLAG;


void setTime(void);
void setDate(void);
void getFunc(unsigned int pressedKey, struct LinkedList* first);
void setS(void);
void setH(void);
void setM(void);


void configKeyPad(void);
int func(void);

#endif