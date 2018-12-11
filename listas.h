#ifndef __listas_h__
#define __listas_h__
#include "item.h"

typedef struct List List;
struct List {
	Item* item;
	List* next;
	List* first;
	List* last;
};

int isEmpty(List* list);
List* addLast(List* list1, List* list2);
List* insert(List* list, Item* item);
List* newItem(Item* item);

#endif