#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
typedef struct pair
{
	struct node * current;
	struct node * prev;
}Pair;
static void DeleteNode(const Item * pi,List * plist);
static void CopyToNode(Node * pnode,Item item);
static Node * AddNode(Item * pi,const List * plist);
static Pair SeekItem(const List * plist,const Item * pi);
void InitializeList(List * plist)
{
	*plist = NULL;
}
bool ListIsEmpty(const List * plist)
{
	return (*plist == NULL) ? true : false;
}
bool ListIsFull(const List * plist)
{
	Node * new_node;

	new_node = (Node *) malloc(sizeof(Node));
	if(new_node == NULL)
		return true;
	else
		return false;
    free(new_node);
}
void EmptyTheList(List * plist)
{
	Node * temp;
	while(*plist != NULL)
	{
		temp = *plist;
		free(temp);
		*plist = (*plist)->next;
	}
}
int ListItemCount(const List * plist)
{
	Node * pnode = *plist;
	int count = 0;
	while(pnode != NULL)
	{
		pnode = pnode->next;
		count++;
	}
	return count;
}
bool InList(const List * plist,const Item * pi)
{
	if(SeekItem(plist,pi).current == NULL)
		return false;
	else
		return true;
}
void Traverse(void(*pfun)(Item item),const List * plist)
{
	Node * pnode = *plist;

	while(pnode != NULL)
	{
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}
bool ReplaceItem(List * plist,Item * m,Item * n)
{
	Node * new_node;
	new_node = SeekItem(plist,m).current;
	if(new_node != NULL)
	{
		CopyToNode(new_node,*n);
		return true;
	}
	else
		return false;
}
bool InsertItem(List * plist,Item * m,Item * n)
{
	//First of all,you need to find the position where you to insert and add a new node after item
	//Then set the next pointer of this new node 
	//Set the previous pointer to point to this new node
	Node * new_node;
	Node * node;
	Node * pnode;

	new_node = AddNode(n,plist);
	node = SeekItem(plist,m).current;
	if(node == NULL)
		return false;
	else
	{
		if(new_node == NULL)
			return false;
		else
		{
			if(node->next == NULL)
				node->next = new_node;
			else
			{
				pnode = node->next;
				node->next = new_node;
				new_node->next = pnode;
			}
			CopyToNode(new_node,*n);
		}
	}
	return true;
}
bool AddItem(List * plist,Item * pi) //Notice that it's better to use a new pointer to make some changes not the *plist pointer
{
	
	//Locate to the end
	//Copy the new item to the list
	Node * new_node;
	Node * scan; //Using a new pointer to find the location needs to be added

	if((new_node = AddNode(pi,plist)) != NULL)
	{
		scan = *plist;
		if(scan == NULL) //Analyst the situation of the first node 
			*plist = new_node; //Notice that here is the *plist pointer
		else
		{
			while(scan->next != NULL) //Notice that here is scan->next pointer not scan pointer
				scan = scan->next;
			scan->next = new_node;
		}
		CopyToNode(new_node,*pi);
        printf("Movie: %s Rating: %d\n",new_node->item.name,new_node->item.rating);
		return true;
	}
	else
		return false;
}
bool DeleteItem(List * plist,const Item * pi)
{
	Node * pnode = SeekItem(plist,pi).current;
	if(*plist == NULL)
	{
		fprintf(stderr,"There is no data.\n");
		return false;
	}
	if(pnode == NULL)
	{
		fprintf(stderr,"Can't find this item!\n");
		return false;
	}
	else
	{
		DeleteNode(pi,plist);
		return true;
	}
}
static void DeleteNode(const Item * pi,List * plist)
{
	Node ** ptr;
	//Deleting a node does not have the complexity of the imagination
	//We should only focus on the situation when it's the first node 
	//and in other situation we set the previous pointer to point to the next pointer
	//In the last we free the memory of the node
	Pair find = SeekItem(plist,pi);
	ptr = &find.current;
	if(find.prev == NULL)
	{
		*plist = (*ptr)->next; //To change the point direction of the list 
		(*ptr)->next = NULL;
		free(*ptr);
	}
	else{
        find.prev->next = (*ptr)->next;
        free(find.current);
	}
}
static Pair SeekItem(const List * plist,const Item * pi)
{
	Pair look;
	Node * pnode = *plist;
	look.prev = NULL;
	look.current = *plist;

	if(look.current == NULL)
		return look;
	while(pnode!= NULL)
	{
		if(strcmp(pi->name,pnode->item.name) == 0 && pi->rating == pnode->item.rating)
			return look;
		look.prev = look.current;
		look.current = pnode->next;
		pnode = pnode->next;
	}
	return look;
}
static void CopyToNode(Node * pnode,Item item)
{
	pnode->item = item;
}
static Node * AddNode(Item * pi,const List * plist)
{
	Node * new_node;

	if(ListIsFull(plist))
		return NULL;
	new_node = (Node *) malloc(sizeof(Node));
	if(new_node == NULL)
	{
		fprintf(stderr,"Error in making nodes.\n");
		return new_node;
	}
	new_node->next = NULL;
	return new_node;
}