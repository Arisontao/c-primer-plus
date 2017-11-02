//1.初始化
//2.确定项树
//3.确定链表是否已满
//4.确定链表是否为空
//5.添加项
//6.删除项
//7.替换项
//8.是每个项都应用函数
//9.删除整个链
//10.插入项
//11.查找项
#ifndef _DLIST_H_
#define _DLIST_H_
#include <stdbool.h>
#define SLEN 20
#define MAXITEMS 10

typedef struct item
{
	char title[SLEN];
	int rating;
}Item;

typedef struct node
{
	Item item;
	struct node * prev;
	struct node * next;
}Node;

typedef struct dlist
{
	int size;
	Node * head;
	Node * tail;
}Dlist;

void InitializeDlist(Dlist * plist);

int DlistItemCount(const Dlist * plist);

bool DlistIsFull(const Dlist * plist);

bool DlistIsEmpty(const Dlist * plist);

bool AddItem(Dlist * plist,Item * pi);

bool DeleteItem(Dlist * plist,Item * pi);

bool ReplaceItem(Dlist * plist,Item * m,Item * n);

bool InsertItem(Dlist * plist,Item * m,Item * n);

bool InList(const Dlist * plist,const Item * pi);

void Traverse(Dlist * plist,void(*pfun)(Item pi));

void DeleteTheList(Dlist * plist);

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct pair
{
	Node * prev;
	Node * current;
}Pair;

static Pair SeekItem(const Dlist * plist,const Item * pi);
static void AddNode(Dlist * plist,Node * new,const Item * pi);
static Node * MakeNode(Item * pi);
static void DeleteNode(Dlist * plist,const Item * pi);

void InitializeDlist(Dlist * plist)
{
	plist->head = NULL;
	plist->tail = NULL;
	plist->size = 0;
}
int DlistItemCount(const Dlist * plist)
{
	return plist->size;
}
bool DlistIsFull(const Dlist * plist)
{
	return (plist->size == MAXITEMS) ? true : false;
}
bool DlistIsEmpty(const Dlist * plist)
{
	return (plist->size == 0) ? true : false;
}
void Traverse(Dlist * plist,void(*pfun)(Item pi))
{
	//这里用一个方向来判断是否到达了底部 这样就更加的简单
	Node * pnode;

	pnode = plist->head;
	if(pnode == NULL)
	{
		fprintf(stderr,"There is no data entered!\n");
		exit(1);
	}
	while(pnode != NULL)
	{
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}
bool InList(const Dlist * plist,const Item * pi)
{
	return (SeekItem(plist,pi).current == NULL) ? false : true;
}
void DeleteTheList(Dlist * plist)
{
	Node * pnode = plist->head;
	while(plist->head != NULL)
	{
		DeleteNode(plist,pnode); //这里就这样 小小的问题
		pnode = pnode->next;
	}
}
bool ReplaceItem(Dlist * plist,Item * m,Item * n)
{
	Pair look = SeekItem(plist,m);

	if(look.current == NULL)
	{
		fprintf(stderr,"Can't find this item!\n");
		return false;
	}
	else
	{
		look.current->item = *n;
		return true;
	}
}
bool AddItem(Dlist * plist,Item * pi)
{
	Node * new_node;
	Node * pnode = plist->head;

	if(DlistIsFull(plist))
	{
		fprintf(stderr,"The list is full!\n");
		return false;
	}
	if(SeekItem(plist,pi).current != NULL)
	{
		fprintf(stderr,"The item is in the list!\n");
		return false;
	}
	if((new_node = MakeNode(pi)) == NULL)
	{
		fprintf(stderr,"Error in making a new node!\n");
		return false;
	}
	plist->tail = new_node;
	plist->size++;
	if(plist->head == NULL)
		plist->head = new_node;
	else
	{
		while(pnode->next != NULL)
			pnode = pnode->next;
		pnode->next = new_node;
		new_node->prev = pnode;
	}
	return true;
}
bool InsertItem(Dlist * plist,Item * m,Item * n)
{
	//插入一个项
	//1.检查是否存在
	//2.确定是否已满
	//3.创建一个新节点
	//4.找到位置插入进去
	//5.设置好指针的双向性
	Node * new_node;

	Pair look = SeekItem(plist,n);
	if(DlistIsFull(plist))
	{
		fprintf(stderr,"The list is full!\n");
		return false;
	}
	if(SeekItem(plist,m).current == NULL)
	{
		fprintf(stderr,"The item you want to insert isn't in the list!\n");
		return false;
	}
	if(look.current != NULL)
	{
		fprintf(stderr,"The item is in the list!\n");
		return false;
	}
	if((new_node = MakeNode(n)) == NULL)
	{
		fprintf(stderr,"Error in making nodes!\n");
		return false;
	}
	else
	{
		AddNode(plist,new_node,m);
		plist->size++;
		return true;
	}
}
bool DeleteItem(Dlist * plist,Item * pi) //这个有问题
{
	Pair look = SeekItem(plist,pi);

	if(DlistIsEmpty(plist))
	{
		fprintf(stderr,"The list is empty!\n");
		return false;
	}
	if(look.current == NULL)
	{
		fprintf(stderr,"The item isn't in the list!\n");
		return false;
	}
	else
	{
		DeleteNode(plist,pi);
		plist->size--;
		return true;
	}
}
static void DeleteNode(Dlist * plist,const Item * pi)
{
	//首先讨论一下删除的是不是第一个节点 只需要讨论两种情况就可以
	Node ** ptr;
	Node * pnode;
	Pair find = SeekItem(plist,pi);
	ptr = &find.current;
	if(find.prev == NULL)
	{
		pnode = (*ptr)->next;
		plist->head = (*ptr)->next;
		pnode->prev = NULL;
		(*ptr)->next = NULL;
		free(find.current);
	}
	else
	{
		//这个我还是差的网上的 才知道...
		//1.把find.current前驱的后继指向find.current的后继
		//2.把find.current的后继的前驱指向find.current的前驱
		(*ptr)->prev->next = (*ptr)->next;
		(*ptr)->next->prev = (*ptr)->prev;
        free(find.current);
	}
}
static void AddNode(Dlist * plist,Node * new,const Item * pi)
{
	//添加节点得分情况讨论
	Pair look = SeekItem(plist,pi);
	Node * pnode = look.current;

	if(look.current->next == NULL)
	{
		look.current->next = new;
		new->prev = look.current;
	}
	else
	{
		new->next = look.current->next;
		look.current->next = new;
		new->prev = pnode;
		pnode->next->prev = new;
	}
}
static Node * MakeNode(Item * pi)
{
	Node * new_node;
	new_node = (Node *) malloc(sizeof(Node));
	if(new_node != NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		new_node->item = *pi;
	}
	return new_node;
}
static Pair SeekItem(const Dlist * plist,const Item * pi)
{
	Pair look;
	Node * pnode = plist->head;
	look.prev = NULL;
	look.current = plist->head;

	if(look.current == NULL)
		return look;
	while(pnode != NULL)
	{
		if(strcmp(look.current->item.title,(*pi).title) == 0 && look.current->item.rating == (*pi).rating) //item哪能这么比较的
			return look;
		look.prev = look.current;
		look.current = look.current->next;
		pnode = pnode->next;
	}
	return look;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void add_movie(Dlist * plist);
void delete_movie(Dlist * plist);
void insert_movie(Dlist * plist);
void replace_movie(Dlist * plist);
void show_movie(Dlist * plist);
void show_list(Item item);
char * s_gets(char * st,int n);
int get_choice(void);
int get_first(void);
int get_let(char * st);
int main(void)
{
	Dlist movie;
	int choice;

	InitializeDlist(&movie);
	while((choice = get_choice()) != 'q')
	{
		switch(choice)
		{
			case 'a': add_movie(&movie); break;
			case 'd': delete_movie(&movie); break;
			case 'i': insert_movie(&movie); break;
			case 'r': replace_movie(&movie); break;
			case 's': show_movie(&movie); break;
		}
	}
	puts("Bye!");

	return 0;
}
void add_movie(Dlist * plist)
{
	Item temp;
	puts("Enter the movie titile:");
	s_gets(temp.title,SLEN);
	puts("Enter the movie rating:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
		continue;
	if(AddItem(plist,&temp))
		printf("Added succesfully!\n");
	else
		printf("Addded failed!\n");
}
void delete_movie(Dlist * plist)
{
	Item temp;
	puts("Enter the movie titile:");
	s_gets(temp.title,SLEN);
	puts("Enter the movie rating:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
		continue;
	if(DeleteItem(plist,&temp))
		printf("Deletion successfully!\n");
	else
		printf("Deletion failed!\n");
}
void insert_movie(Dlist * plist)
{
	Item temp;
	Item temp2;
	puts("Enter the movie titile:");
	s_gets(temp.title,SLEN);
	puts("Enter the movie rating:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
		continue;
	puts("Enter the movie titile:");
	s_gets(temp2.title,SLEN);
	puts("Enter the movie rating:");
	scanf("%d",&temp2.rating);
	while(getchar() != '\n')
		continue;
	if(InsertItem(plist,&temp,&temp2))
		puts("Insertion succesfully!");
	else
		puts("Insertion failed!");
}
void replace_movie(Dlist * plist)
{
	Item temp;
	Item temp2;
	puts("Enter the movie titile:");
	s_gets(temp.title,SLEN);
	puts("Enter the movie rating:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
		continue;
	puts("Enter the movie titile:");
	s_gets(temp2.title,SLEN);
	puts("Enter the movie rating:");
	scanf("%d",&temp2.rating);
	while(getchar() != '\n')
		continue;
	if(ReplaceItem(plist,&temp,&temp2) == true)
		puts("Replace succesfully!");
	else
		puts("Replace failure!");
}
void show_movie(Dlist * plist)
{
	Node * pnode = plist->tail;
	puts("p to show list in positive order,r to show list in reverse order.");
	puts("Enter your choice:");
	if(get_let("pr") == 'p')
		Traverse(plist,show_list);
	else
	{
		while(pnode != NULL)
		{
			printf("Movie: %s Rating: %d\n",pnode->item.title,pnode->item.rating);
			pnode = pnode->prev;
		}
	}
}
void show_list(Item item)
{
	printf("Movie: %s Rating: %d\n",item.title,item.rating);
}
int get_let(char * st)
{
	int ch;

	ch = get_first();
	while(strchr(st,ch) == NULL)
	{
		printf("Enter a character in %s",st);
		ch = get_first();
	}
	return ch;
}
int get_choice(void)
{
	int ch;
	puts("Enter the operation you want to do:");
	puts("a)add movie		d)delete movie");
	puts("i)insert movie		r)replace movie");
	puts("s)show movie		q)quit");
	ch = get_first();
	while(strchr("adirsq",ch) == NULL)
	{
		puts("Enter a,d,i,r,s or q:");
		ch = get_first();
	}
	return ch;
}
int get_first(void)
{
	int ch;
	ch = getchar();
	while(getchar() != '\n')
		continue;
	return ch;
}
char * s_gets(char * st,int n)
{
	char * find;
	char * ret_val;

	ret_val = fgets(st,n,stdin);
	if(ret_val)
	{
		find = strchr(st,'\n');
		if(find)
			*find = '\0';
		else
			while(getchar() != '\n')
				continue;
	}
	return ret_val;
}
