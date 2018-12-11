#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

int isEmpty (List* list) {
	if (list == NULL)
		return 1;
	return 0;
}

List* addLast (List* list1, List* list2) {
	list1 -> last -> next = list2;
	list1 -> last = list2 -> last;

	return list1;
}

List* insert (List* list, Item* item) {
	if (isEmpty(list))
		return newItem(item);
	return addLast(list, newItem(item));
}

List* newItem(Item* item) {
	List* list = (List *)malloc(sizeof(List));

	list -> item = item;
	list -> next = NULL;
	list -> last = list;

	return list;
}