#ifndef structs_h
#define structs_h

struct LinkedList
{
  int id;
  double sensorData;//data
  unsigned char YY:7;//year
  unsigned char MM:4;//month
  unsigned char DD:5;//day
  
  
  unsigned char hh:5; //hour 
  unsigned char mm:6;//minute
  unsigned char ss:6;//seconds
  struct LinkedList* next;//pointer to next element in list
};

struct minMaxAvgNode
{
  unsigned char day:5;
  unsigned char minH:5; //hour 
  unsigned char minM:6;//minute
  unsigned char minS:6;//seconds
  int min;
  
  unsigned char maxH:5; //hour 
  unsigned char maxM:6;//minute
  unsigned char maxS:6;//seconds
  int max;

  int avarage;
  int antal:11;
};
#endif