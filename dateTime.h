#ifndef dateTime_h
#define dateTime_h
 extern unsigned int s;//seconds, unconfigurable

 extern unsigned int m; //miutes, configurable
 
 extern unsigned int h; //hours, configurable

 
 extern unsigned int mFLAG; //1 if you want to set minute tens, 2 if you want to set ones
 extern unsigned int hFLAG;//1 if you want to set hour tens, 2 if you want to set ones

 extern unsigned int day; //day, configurable

 extern unsigned int month; //month, configurable

 extern unsigned int year; //year, configurable
 
 extern unsigned int dayFLAG; //1 if you want to set day tens, 2 if you want to set ones
 extern unsigned int monthFLAG;//1 if you want to set month tens, 2 if you want to set ones
 extern unsigned int yearFLAG;//1 if you want to set year tens, 2 if you want to set ones
 
 
 void goTime();
 void setH(void);
 void setM(void);
 void setTime(void);
 void printTime();
 void setDate(void);
 void setYear();
 void setMonth();
 void setDay();
 void goDate();
 void printDate();
 
 void printDateTime();
 
 int getDaysInMonth(unsigned int month);
 
#endif