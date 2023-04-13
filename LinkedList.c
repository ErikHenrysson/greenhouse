#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void freeList(struct LinkedList** list);

int isEmpty(struct LinkedList** first)
{
  if ((*first) == NULL)
  return 1;
  return 0;
}

void insertFirst(struct LinkedList** first, struct LinkedList *el)
{
  if(isEmpty(first))
  {
  *first = el;
  (*first)->next = NULL;
  }
  else
  {
    struct LinkedList* temp = *first;
    *first = el;
    el->next = temp;
  }

}

void insertLast(struct LinkedList** first, struct LinkedList *el)
{
  if(isEmpty(first))
  *first = el;
  else
  {
    struct LinkedList* temp = *first;

    while(temp->next != NULL)//goes to the end of the list 
    temp=temp->next;

    temp->next = el;//point to the "new last" element
  }
}

int isMember(struct LinkedList**first, struct LinkedList *el)//similarly to printlist it itterates the list and checks if there is a node with the same id and sensordata to be found
{
  if(isEmpty(first)) //if its empty it cant contain the element
  return 0;

  else
  {
    struct LinkedList *temp; //temporary address for itteration
    temp = *first;
      while (temp != NULL)
      {
        if(el==temp)//if both the id and the sensordata is the same you found it and can stop
        return 1;
        temp=temp->next;// if not, continue itteration
      }
  }

  return 0;
}

void printList(struct LinkedList* first) //prints out the list from start to end
{
  if(isEmpty(&first)) //if the list is empty
  {
    printf("The list is empty!\n");
    return;
  }
  printf("------------------------------------------\n");
  struct LinkedList *temp; //temporär address för itteration
  temp = first;
  while (temp != NULL)
  {
    printf("id: %d\nSensordata: %f\n\n", temp->id, temp->sensorData);//print element
    temp = temp->next;//go to next
  }
    printf("------------------------------------------\n");
  return;
}

void Remove(struct LinkedList **first, struct LinkedList* el)
{
  if (!isMember(first, el)) //if the list doesnt contain the element, it cant do anything
  {
    printf("The element was not in the list\n");
    return;
  }
//fungerar inte om man tar bort det sista elementet i listan
  //if the element exists: find it and delete it
  struct LinkedList* temp;
  temp = *first; //temporary node for itteration

  if((temp == el)&(temp->next ==NULL)) //if its the first element and there is no after
      {
      *first = NULL;
      return;
      }
  else if((temp == el)&(temp->next !=NULL)) //if its the first element and there are elements after
  {
    *first = temp->next;
    return;
  }

  while((temp->next)!=el)//if its somewhere else, find the element bofore it
  {
    temp=temp->next;
  }
  
  temp->next = el->next;
}

struct LinkedList* createNode(int id, double sensorData)//creates a node with next set to null
{
  struct LinkedList* Node = (struct LinkedList*)malloc(1*sizeof(struct LinkedList));
  if(Node == 0)
  printf("Out of memory!");
  // kolla om det finns nått space!!!!
  
  Node->sensorData= sensorData;
  Node->id = id;
  Node->next = NULL;
  return Node;
}


struct LinkedList* createTempNode(struct LinkedList** first, int id, double sensordata, int year,int month,int day,int hour,int minute,int second)
{
struct LinkedList* Node = (struct LinkedList*)malloc(1*sizeof(struct LinkedList));
if(Node == 0)
{
  printf("Out of memory!\n"); //free list, gör en ny nod
  freeList(first);
  Node = (struct LinkedList*)malloc(1*sizeof(struct LinkedList));
}
Node->id = id;
Node->sensorData= sensordata;
Node->next = NULL;
Node->YY = year;
Node->MM = month;
Node->DD = day;
Node->hh = hour;
Node->mm = minute;
Node->ss = second;

return Node;
}

struct LinkedList* readSensor(int id)
{
  struct LinkedList* list;
  double sensorData = (double)(rand())/RAND_MAX;
  
  list = createNode(id, sensorData);

  return list;
}

void freeList(struct LinkedList** list)
{
  struct LinkedList* temp;
  while(*list != NULL)
  {
    temp = (*list)->next;
    free(*list);
    *list =temp;    
  }
  //printf("Print after free \n");
  //printList(*list);
  return;
}

void sortList(struct LinkedList** first,struct LinkedList** sorted)
{
  struct LinkedList* temp;
  struct LinkedList* max;

  //for (int i = 0; i<10 ; i++)
  while(!isEmpty(first)) //does this until first is empty
  {
  max = *first;
  temp = *first;
    while(temp!=NULL)//gå igenom listan
    {
      if((max->sensorData)<(temp->sensorData))//checks if bigger
      {
        max = temp;
      }
      temp=temp->next;
    }
  Remove(first,max);//removes the biggest from first
  insertFirst(sorted,max);//inserts it into the sorted list
  }

  free(first);//clears the empty list from memory
  //printf("Print efter sortlist:\n");
  //printList(*sorted);
  freeList(sorted);

  //free sorted eller first, välj någon

}

