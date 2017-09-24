#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 10 /* maximum number of books */
#define CONTINUE 0
#define DONE 1
struct book { /* set up book template */
 char title[MAXTITL];
 char author[MAXAUTL];
 float value;
};
struct pack {
 struct book book; // different namespaces for two book identifiers
 bool delete_me;
};
char * s_gets(char * st, int n);
int getlet(const char * s);
int getbook(struct pack * pb);
void update(struct pack * item);
int main(void)
{
	struct pack library[MAXBKS]; /* array of structures */
	int count = 0;
	int deleted = 0;
	int index, filecount, open;
	int max;
	FILE * pbooks;
	int size = sizeof (struct book);
	if ((pbooks = fopen("book.dat", "r")) != NULL)
	{
		while (count < MAXBKS && fread(&library[count], size,1, pbooks) == 1)
		{
			if (count == 0)
				puts("Current contents of book.dat:");
			printf("%s by %s: $%.2f\n",library[count].book.title,library[count].book.author, library[count].book.value);
			printf("Do you wish to change or delete this entry?<y/n> ");
			if (getlet("yn") == 'y')
			{
				printf("Enter c to change, d to delete entry: ");
				if (getlet("cd") == 'd')
				{
					library[count].delete_me = true;
					deleted++;
					puts("Entry marked for deletion.");
				}
				else
					update(&library[count]);
			}
			count++;
		}
		fclose(pbooks);
	}
	filecount = count - deleted; 
	if (count == MAXBKS)
	{
		fputs("The book.dat file is full.", stderr);
		exit(EXIT_FAILURE);
	}
	puts("Please add new book titles.");
	puts("Press [enter] at the start of a line to stop."); 
	open = 0;
	while (filecount < MAXBKS)
	{
		if (filecount < count)
		{
			while (library[open].delete_me == false)
				open++;
			if (getbook(&library[open]) == DONE)
				break;
		}
		else if (getbook(&library[filecount]) == DONE) 
			break;
		filecount++;
		if (filecount < MAXBKS)
			puts("Enter the next book title.");
	}
	max = filecount;
	if(max < count)
		max = count;
	puts("Here is the list of your books:"); 
	for (index = 0; index < max; index++)
		if (library[index].delete_me == false)
			printf("%s by %s: $%.2f\n",library[index].book.title,library[index].book.author, library[index].book.value);
	if ((pbooks = fopen("book.dat", "w")) == NULL)
	{
		fputs("Can't open book.dat file for output\n",stderr);
		exit(EXIT_FAILURE);
	}
	for (index = 0; index < max; index++) 
		if (library[index].delete_me == false)
			fwrite(&(library[index].book), size, 1, pbooks); 
	fclose(pbooks);
	puts("Done!");
	return 0;
}
int getlet(const char * s)
{
	char c;

	c = getchar();
	while (strchr(s, c) == NULL)
	{
		printf ("Enter a character in the list %s\n", s);
		while( getchar() != '\n')
			continue;
		c = getchar();
	}
	while (getchar() != '\n')
		continue;

	return c;
}
int getbook(struct pack * pb)
{
	int status = CONTINUE;
	if (s_gets(pb->book.title, MAXTITL) == NULL || pb->book.title[0] == '\0') 
		status = DONE;
	else
	{
		printf ("Now enter the author: ");
		s_gets (pb->book.author, MAXAUTL);
		printf ("Now enter the value: ");
		while (scanf("%f", &pb->book.value ) != 1)
		{
			puts("Please use numeric input");
			scanf("%*s"); 
		}
		while (getchar() != '\n')
			continue; /*clear input line */
		pb->delete_me = false; 
	}
	return status;
}
void update(struct pack * item)
{
	struct book copy;
	char c;

	copy = item->book;
	puts("Enter the letter that indicates your choice:");
	puts("t) modify title a) modify author");
	puts("v) modify value s) quit, saving changes");
	puts("q) quit, ignore changes");
	while ( (c = getlet("tavsq")) != 's' && c != 'q')
	{
		switch ( c )
		{
			case 't' : puts("Enter new title: ");
						s_gets (copy.title, MAXTITL);
						break;
			case 'a': puts("Enter new author: ");
						s_gets (copy.author, MAXAUTL);
						break;
			case 'v' : puts("Enter new value: ");
						while (scanf("%f", &copy.value) != 1)
						{
							puts ("Enter a numeric value: ");
							scanf("%*s");
						}
						while( getchar() != '\n')
							continue;
						break;
		}
		puts("t) modify title a) modify author");
		puts("v) modify value s) quit,saving changes");
		puts("q) quit, ignore changes");
	}
	if (c == 's')
		item->book = copy;
}
char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}
