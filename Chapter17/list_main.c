#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
int get_choice(void);
int get_first(void);
void show_movies(Item item);
void add_movie(List * plist);
void replace_movie(List * plist);
void input(Item * m,Item * n);
void delete_movie(List * plist);
void insert_movie(List * plist);
void seek_movie(const List * plist);
char * s_gets(char * st,int n);
//First of all,you should notice that you mustn't change the point of 
//			*plist pointer when you don't need need to change the point of the list
//Otherwise,the point of the orginal list will be changed.
int main(void)
{
	List movies;
	int choice;

	InitializeList(&movies);
	if(ListIsFull(&movies))
	{
		fprintf(stderr,"No memory avaialbe! Bye!\n");
		exit(1);
	}
	while((choice = get_choice()) != 'q')
	{
		switch(choice)
		{
			case 'a': add_movie(&movies); break;
			case 'd': delete_movie(&movies); break;
			case 'i': insert_movie(&movies); break;
			case 'e': seek_movie(&movies); break;
			case 's': 	if(ListIsEmpty(&movies))
							printf("No data entered.\n");
						else
						{
							printf("Here is the movie list:\n");
							Traverse(show_movies,&movies);
						}
						break;
			case 'r': replace_movie(&movies); break;
		}
	}
	printf("You have entered %d movies.\n",ListItemCount(&movies));
	EmptyTheList(&movies);
	printf("Bye!\n");

	return 0;
}
int get_choice(void)
{
	int ch;
	char * find;
	puts("Please enter the operation you want to do:");
	puts("a)add movie		d)delete movie");
	puts("i)insert movie		e)seek movie");
	puts("r)replace movie		s)show movie");
	puts("q)quit");
	ch = get_first();

	while((find = strchr("aidersq",ch))== NULL)
	{
		puts("Please enter a,d,i,e,s,r or q:");
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
void replace_movie(List * plist)
{
	Item temp;
	Item replace;

	if(ListIsEmpty(plist))
	{
		printf("No data entered.\n");
		return;
	}
	else
	{
		printf("Here is the movie list:\n");
		Traverse(show_movies,plist);
	}
	input(&temp,&replace);
	if(ReplaceItem(plist,&temp,&replace) == true)
		puts("Replace completed.");
	else
		puts("Replace failed.");
}
void insert_movie(List * plist)
{
	Item temp;
	Item additem;

	if(ListIsEmpty(plist))
	{
		puts("Enter the new film title:");
		s_gets(temp.name,SLEN);
		puts("Enter the rating:");
		scanf("%d",&temp.rating);
		while(getchar() != '\n')
			continue;
		AddItem(plist,&temp);
	}
	else
	{
		printf("Here is the movie list:\n");
		Traverse(show_movies,plist);
	}
	input(&temp,&additem);
	if(InsertItem(plist,&temp,&additem) == true)
		puts("Insertion completed.");
	else
		puts("Insertion failed.");
}
void seek_movie(const List * plist)
{
	Item temp;

	if(ListIsEmpty(plist))
	{
		fprintf(stderr,"The movie list is empty!\n");
		return;
	}
	else
	{
		printf("Here is the movie list:\n");
		Traverse(show_movies,plist);
	}
	puts("Enter name of film you wish to find:");
	s_gets(temp.name,SLEN);
	puts("Enter the rating of film you wish to find:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
			continue;
	if(InList(plist,&temp))
		puts("The film is in the list.");
	else
		puts("The film isn't in the list.");
}
void delete_movie(List * plist)
{
	Item temp;

	if(ListIsEmpty(plist))
	{
		printf("No data entered.\n");
		return;
	}
	else
	{
		printf("Here is the movie list:\n");
		Traverse(show_movies,plist);
	}
	puts("Enter name of film you wish to delete:");
	s_gets(temp.name,SLEN);
	puts("Enter the film rating you wish to delete:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
			continue;
	if(DeleteItem(plist,&temp)) //Input a complete item
		puts("Deletion completed.");
	else
		puts("Deletion failed.");
}
void add_movie(List * plist)
{
	Item temp;

	if(ListIsFull(plist))
	{
		fprintf(stderr,"The list now is full!\n");
		return;
	}
	puts("Enter first film title:");
	s_gets(temp.name,SLEN);
	puts("Enter the film rating:");
	scanf("%d",&temp.rating);
	while(getchar() != '\n')
			continue;
	if(AddItem(plist,&temp) == false)
	{
		fprintf(stderr,"Problem allocating memory!\n");
		return;
	}
}
void input(Item * m,Item * n)
{
	puts("Enter the position of film you want to insert:");
	s_gets((*m).name,SLEN);
	puts("Enter the rating of film:");
	scanf("%d",&(*m).rating);
	while(getchar() != '\n')
			continue;
	puts("Enter the new film title:");
	s_gets((*n).name,SLEN);
	puts("Enter the rating of new film:");
	scanf("%d",&(*n).rating);
	while(getchar() != '\n')
			continue;
}
void show_movies(Item item)
{
	printf("Movie: %s Rating: %d\n",item.name,item.rating);
}
char * s_gets(char * st,int n)
{
	char * ret_val;
	char * find;

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
