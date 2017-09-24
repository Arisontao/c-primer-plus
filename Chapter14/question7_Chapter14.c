#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 5
struct book{
	char title[MAXTITL];
	char author[MAXAUTL];
	double value;
};
struct pack{
	struct book book2;
	bool delete_me;
};
int get_let(const char * st);
char get_choice(void);
char get_first(void);
void modify_struct(struct pack * ptr);
int get_book(struct pack * ptr); //This function is used to judge whether it successed in reading a struct
char *s_gets(char * st,int n);
int main(void)
{
	struct pack library[MAXBKS];
	FILE *fp;
	int count = 0;
	int size = sizeof(struct book); //Note that the size here is the size of book struct which is a small detail you should pay attention to
	int filecount;
	int open;
	int max;
	int i;
	int delete_book = 0;

	if((fp = fopen("book.dat","r")) != NULL)
	{
		while(count < MAXBKS && fread(&library[count],size,1,fp) == 1)
		{
			if(count == 0)
				puts("Current book:");
			printf("%s by %s: $%.2lf\n",library[count].book2.title,library[count].book2.author,library[count].book2.value);
			puts("Do you want to make some changes with this book?<y/n>");
			if(get_let("yn") == 'y')
			{
				puts("You have two choice,m to modify book details,d to delete this book:");
				if(get_let("md") == 'd')
				{
					library[count].delete_me = true;
					puts("This book has been marked for deleteion.");
					delete_book++;
				}
				else
					modify_struct(&library[count]);
			}
			count++;
		}
		fclose(fp);
	}
	filecount = count - delete_book;
	puts("Please enter new book's title:");
	puts("Press [enter] at the start of a line to stop.");
	open = 0; // We should put the variable open outside because there is no need to look for the deleted structure from the beginning
	while(filecount < MAXBKS)
	{
		if(filecount < count)
		{
			while(library[open].delete_me == false) //Ignoring a very important case is that when count < MAXBKS,filecount is equal to count
				open++;
			if(get_book(&library[open]) == 0)
				break;
		}
		else if(get_book(&library[filecount]) == 0)
			break;
		filecount++; //After adding a new struct,increasing the filecount
		//The location of filecount should be palaced outside the if statement
		if (filecount < MAXBKS)
			puts("Enter the next book title.");
	}
	puts("Here is the list of your books:");
	/*The question here is if you delete a struct without adding a new struct,the number of filecount is less than count
	 ,but you don't know which variable is deleted,so you have to traverse the structure array with count
	 And after adding a new structure,the number of filecount is more than count,so you need to traverse the structure array with filecount
	*/
	max = filecount;
	if(max < count)
		max = count;  //max is the large number between the filecount and count
	for(i = 0;i < max;i++)
		if(library[i].delete_me == false) //Note that to check if the structure is been marked for deletion when printing
			printf("%s by %s: $%.2lf\n",library[i].book2.title,library[i].book2.author,library[i].book2.value); //Note that the name of variable
	if((fp = fopen("book.dat","w")) == NULL) //To check whether you open the same file
	{
		puts("Can't open e.dat file.");
		exit(1);
	}
	//There is no need to use the else statement because it exits the program when it can't open the file
	for(i = 0;i < max;i++)
		if(library[i].delete_me == false)
			fwrite(&(library[i].book2),size,1,fp); //It writes into the book2 element of the structure
	fclose(fp);
	puts("Done.");

	return 0;
}
void modify_struct(struct pack * ptr)
{
	struct book copy;
	int choice;

	copy = ptr->book2;
	while((choice = get_choice()) != 'q' && choice != 's') //Note that the use of stop point
	{
		switch(choice)
		{
			case 'a':	puts("Enter the new title:");
						s_gets(copy.title,MAXTITL); //Here we assign to the copy structure
						break;
			case 'b':	puts("Enter the new author:");
						s_gets(copy.author,MAXAUTL);
						break;
			case 'c':	puts("Enter the new book value:");
						while(scanf("%lf",&copy.value) != 1)
						{
							puts("Please enter again:");
							scanf("%*s"); //It equals to this statement "scanf("%lf",&copy.value)"
						}
						while(getchar() != '\n')
							continue;
						break;
		}
	}
	if(choice == 's')
		ptr->book2 = copy;
}
char get_choice(void)
{
	int ch;
	puts("Enter the operation you want to do:");
	puts("a) modify title		b) modify author");
	puts("c) modify value		s) quit,saving changes");
	puts("q) quit,ignore changes");
	ch = get_first();
	while((ch < 'a' || ch > 'c') && ch != 'q' && ch != 's')
	{
		puts("Please enter a,b,c,s or q");
		ch = get_first();
	}
	return ch;
}
char get_first(void)
{
	int ch;
	ch = getchar();
	while(getchar() != '\n')
		continue;
	return ch;
}
int get_book(struct pack * ptr)
{
	int status = 1;
	if(s_gets(ptr->book2.title,MAXTITL) == NULL || ptr->book2.title[0] == '\0') //The order of Or statement is executed from left to right
		status = 0;
	else{
		puts("Please enter author:");
		s_gets(ptr->book2.author,MAXAUTL);
		puts("Please enter value:");
		while(scanf("%lf",&ptr->book2.value) != 1)
		{
			puts("Please enter again:");
			scanf("%*s");
		}
		while(getchar() != '\n')
			continue;
		ptr->delete_me = false;
	}
	return status;
}
int get_let(const char * st)
{
	int ch;

	ch = getchar();
	while(strchr(st,ch) == NULL)
	{
		printf("Please enter a character in the list %s.\n",st);
		while(getchar() != '\n')
			continue;
		ch = getchar();
	}
	while(getchar() != '\n')
		continue;
    return ch;
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
