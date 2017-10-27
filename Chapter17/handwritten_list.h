#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>
#define SLEN 20
typedef struct item
{
	char name[SLEN];
	int rating;
}Item;

typedef struct node
{
	Item item;
	struct node * next;
}Node;

typedef Node * List;

void InitializeList(List * plist);

bool ListIsFull(const List * plist);

bool ListIsEmpty(const List * plist);

void EmptyTheList(List * plist);

int ListItemCount(const List * plist);

void Traverse(void(*pfun)(Item item),const List * plist);

bool InList(const List * plist,const Item * pi);

bool DeleteItem(List * plist,const Item * pi);

bool AddItem(List * plist,Item * pi);

bool InsertItem(List * plist,Item * m,Item * n);

bool ReplaceItem(List * plist,Item * m,Item * n);

#endif