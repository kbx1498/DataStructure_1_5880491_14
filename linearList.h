#pragma once

typedef struct ElementType {
	int coef, expo;
} elementType;

typedef struct ListType {
	int size;
	int last;
	int move;
	elementType* array;
} listType;

listType* createList(int size);
elementType readItem(listType* list, int index);
elementType deleteItem(listType* list, int index);
int insertItem(listType* list, int index, elementType item);
int printList(listType* list);
int initList(listType* list);
int ordered_insertItem(listType* list, elementType item);
int destroyList(listType* list);
elementType getNullItem();  