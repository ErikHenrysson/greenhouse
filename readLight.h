#ifndef readLight_h
#define readLight_h
extern int light1;
extern int light2;
extern int lightFLAG;
void goLight();
void configLight();
void ADC_Handler(void);
void startMeasurement();
void printVoltage();
#endif