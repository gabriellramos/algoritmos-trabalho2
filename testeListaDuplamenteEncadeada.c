#include <stdlib.h>
#include <stdio.h>

typedef struct Item
{
   int start;
   int time;
   int timeF;
   struct Item* prev;
   struct Item* next;
} Item;

typedef struct
{
   int size;
   Item* first;
   Item* last;
} List;

static void insert(List *list, int start, int time)
{
   printf("* ===\n");

   Item *newItem = (Item*)malloc(sizeof(Item));
   newItem->start = start;
   newItem->time = time;

   if (list->size == 0)
   {
      printf("* inserindo elemento %d em lista vazia\n", start);
      newItem->timeF = time;//tempo de exeucução igual ao tempo final
      list->first = newItem;
      list->last = newItem;
      newItem->prev = newItem;
      newItem->next = newItem;
      list->size = 1;
      return;
   }

   if ((start <= list->first->start) && (time < list->first->time))
   {
      printf("* inserindo processo %d antes do primeiro\n", start);
      list->first->prev = newItem;
      list->last->next = newItem;
      newItem->prev = list->last;
      newItem->next = list->first;
      list->first = newItem;
      list->size++;
      return;
   }

   if (start > list->last->start)
   {
      printf("* inserindo elemento %d depois do ultimo\n", start);
      list->last->next = newItem;
      list->first->prev = newItem;
      newItem->prev = list->last;
      newItem->next = list->first;
      list->last = newItem;
      list->size++;
      return;
   }

   printf("* inserindo elemento %d intermediario\n", start);
   Item* item = list->first;
   int i;
   for (i = 0; i < list->size; i++)
   {
      if (item->time > time)
         break;
      item = item->next;
   }

   item->prev->next = newItem;

   newItem->prev = item->prev;
   newItem->next = item;

   item->prev = newItem;

   list->size++;
}

static void print(List* list)
{
   printf("* ---\n");
   printf("* tamanho da lista: %d\n", list->size);
   Item* item = list->first;
   int i;
   for (i = 0; i < list->size; i++)
   {
      printf("* list[%d] = %d - %d - d\n", i, item->start, item->time, item->timeF);
      item = item->next;
   }
}


int main(void)
{
   List list = { 0 };
   print(&list);

   insert(&list, 0,5);  // primeiro elemento
   print(&list);

   insert(&list, 0,2); // antes do primeiro elemento
   print(&list);

   insert(&list, 1,4); // depois do ultimo elemento
   print(&list);

   insert(&list, 3,3);  // elemento intermediario
   print(&list);
   
}
