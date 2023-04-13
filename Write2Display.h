#ifndef dispfunc_h
#define dispfunc_h
void SetDBInput();//
void SetDBOutput();//
void clearDB();//
void Init_Display();//
void ActivateLCD();//
void Write_Command_2_Display(unsigned char command);//
void Write_Data_2_Display(unsigned char Data);//
void Delay();//
void configDisp();
void setCursor(void);
void clearDisplay(void);
void printLetter(unsigned char letter);
void setCursorPointer(int row, int col);

unsigned char Read_Status_Diplay();//
void PrintNum(unsigned char num);//
#endif