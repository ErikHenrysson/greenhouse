
#ifndef LinkedList_h
#define LinkedList_h
#include "structs.h"

void insertFirst(struct LinkedList**first, struct LinkedList *el);
struct LinkedList* createNode(int id, double sensorData);
int isMember(struct LinkedList**first, struct LinkedList *el);
void printList(struct LinkedList*first);
void Remove(struct LinkedList **first, struct LinkedList*el);
void insertLast(struct LinkedList** first, struct LinkedList *el);
void sortList(struct LinkedList** first, struct LinkedList** sorted);
int isEmpty(struct LinkedList** first);
struct LinkedList * readSensor(int id);
void freeList(struct LinkedList ** list);
struct LinkedList* createTempNode(struct LinkedList** first, int id, double sensordata, int year,int month,int day,int hour,int minute,int second);


#endif