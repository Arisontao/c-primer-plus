#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXNAME 40
#define MAXSEAT 12
struct airplane {
	char fname[MAXNAME];
	char lname[MAXNAME];
	int seat_number;
	bool seat_reservation;
};
int * input(int * n);
char get_choice(void);
char get_choice2(void);
char * s_gets(char *st,int n);
char get_first(void);
void show_reserved_seat(struct airplane * ptr[]);
void show_number_seat(struct airplane * ptr[]);
void show_list_seat(struct airplane * ptr[]);
void show_alpha_seat(struct airplane * ptr[]);
void assign_seat(struct airplane * ptr[]);
void delete_seat(struct airplane * ptr[]);
int main(void)
{
	struct airplane seat[MAXSEAT];
	struct airplane *pointer[MAXSEAT];
	int i;
	int choice;

	for(i = 0;i < MAXSEAT;i++)
	{
		pointer[i] = &seat[i]; //Using the pointer array to modify the contents of structure not the initialization of structure
		pointer[i]->seat_number = i + 1;
		pointer[i]->seat_reservation = false;
	}
	while((choice = get_choice()) != 'f')
	{
		switch(choice)
		{
			case 'a':	show_number_seat(pointer);
				break;
			case 'b':	show_list_seat(pointer);
				break;
			case 'c':	show_alpha_seat(pointer);
				break;
			case 'd':	assign_seat(pointer);
				break;
			case 'e':	delete_seat(pointer);
				break;
		}
	}
	puts("Done.");

	return 0;
}
void delete_seat(struct airplane * ptr[])
{
	int seatnum;
	int choice2;
	int n;
	int i;
	int flag = 0; //A variable to judge if all the seats are empty
	struct airplane pointer2[MAXSEAT];
	//Traversing the whole array with flag variable if you want to exit this function when all the seats are empty
	for(n = 0;n < MAXSEAT;n++)
        pointer2[n] = *ptr[n];
	while((choice2 = get_choice2()) != 'q' && choice2 != 'b') //Using return statement to break the loop is better than using goto statement
	{
		switch(choice2)
		{
			case 'a':	flag = 0; //Remember to set flag variable to 0
						for(n = 0;n < MAXSEAT;n++)
							if(pointer2[n].seat_reservation == false)
								flag++;
						if(flag == MAXSEAT)
						{
							puts("There are no seats have been reserved.");
							puts("Deletion failed."); //Only after inputing a number should you skip the break line
							return;
						}
						puts("Enter the number of seat you want to cancel reservation:");
						seatnum = *input(&seatnum);
						flag = 0; //Remember to set flag variable to 0
						for(n = 0;n < MAXSEAT;n++)
							if(pointer2[n].seat_reservation == false)
								flag++;
						if(flag == MAXSEAT)
						{
							puts("There are no seats have been reserved.");
							puts("Deletion failed.");
							while(getchar() != '\n')
								continue;
							return;
						}
						while(pointer2[seatnum - 1].seat_reservation == false) //Here we deal with the case when all the seats are empty
						{
							puts("This seat is empty,please enter a seat which have been reserved.");
							puts("Here is the number of seats which have been reserved:");
							for(i = 0;i < MAXSEAT;i++)
								if(pointer2[i].seat_reservation == true)
									printf("%d ",pointer2[i].seat_number);
							putchar('\n');
							puts("Please enter number:");
							seatnum = *input(&seatnum);
						}
						while(getchar() != '\n') //Using this function after all input operations are finished
							continue;
						pointer2[seatnum - 1].fname[0] = '\0';
						pointer2[seatnum - 1].lname[0] = '\0';
						pointer2[seatnum - 1].seat_reservation = false;
						break;
		}
	}
	if(choice2 == 'b')
		for(n = 0;n < MAXSEAT;n++)
			*ptr[n] = pointer2[n];
	puts("Deletion completed.");
}
char get_choice2(void)
{
	int ch;
	puts("Enter the operation you want to do:");
	puts("a) cancel reservation		b)saving changes,and quit");
	puts("q) quit");
	ch = get_first();
	while((ch < 'a' || ch > 'b') && ch != 'q')
	{
		puts("Please enter a,b or q:");
		ch = get_first();
	}
	return ch;
}
void assign_seat(struct airplane * ptr[])
{
	int seatnum;
	int * p;
	char name[MAXNAME];
	puts("Enter empty line at the start to stop.");
	puts("Enter the customer first name:");
	if(s_gets(name,MAXNAME) != NULL && name[0] != '\0')
	{
		puts("Enter the seat number you want to assign:");
		p = input(&seatnum);
		while(ptr[*p - 1]->seat_reservation == true)
		{
			puts("This seat have been reserved,please choose a empty seat.");
			show_number_seat(ptr);
			puts("Please enter number:");
			p = input(&seatnum);
		}
		while(getchar() != '\n') //Here we should use this function to skip the break line
			continue;
		strcpy(ptr[*p - 1]->fname,name);
		puts("Enter the customer last name:");
		s_gets(ptr[*p - 1]->lname,MAXNAME);
		ptr[*p - 1]->seat_reservation = true; //Remember to set seat_reservation to true after assigning seats
	}
}
void show_alpha_seat(struct airplane * ptr[])
{
	int i,j;
	struct airplane * pointer[MAXSEAT]; //copy of the struct pointer array
	struct airplane * temp;
	char name[MAXSEAT][2 * MAXNAME];
	char temp_name[2 * MAXNAME];
	int m,n;
	int flag = 0; //Using this variable to judge if all the seats are empty

	for(n = 0;n < MAXSEAT;n++)
    {
		pointer[n] = ptr[n];
		if(pointer[n]->seat_reservation == true)
		{
			name[n][0] = '\0'; //Set 0 to the string array before using it
			strncat(name[n],pointer[n]->fname,MAXNAME); //There is no need to set 0 to all array members
			strncat(name[n],pointer[n]->lname,MAXNAME);
		}
	}
	for(n = 0;n < MAXSEAT;n++)
		if(pointer[n]->seat_reservation == false)
			flag++;
	for(i = 0;i < MAXSEAT - 1;i++)
	{
		for(j = i + 1;j < MAXSEAT;j++)
		{
			if(name[i][0] != '\0' && name[j][0] != '\0') //We use MAXSEAT number as the termination condition,because some of the array members is empty and we should sort it
			{
				if(strcmp(name[i],name[j]) > 0) //When exchanging,you need to unify the variable
				{
					temp = pointer[i]; //Here we swap the two members
					pointer[i] = pointer[j];
					pointer[j] = temp;
					strcpy(temp_name,name[i]); //Using strcpy function to swap each two strings
					strcpy(name[i],name[j]);
					strcpy(name[j],temp_name);
				}
			}
		}
	}
	if(flag == MAXSEAT)
		puts("There are no seats have been reserved.");
	else
	{
		puts("Here is the alphabetical list of seats:");
		for(m = 0;m < MAXSEAT;m++)
		if(pointer[m]->seat_reservation == true)
		{
			printf("First name: %s\n",pointer[m]->fname);
			printf("Last name: %s\n",pointer[m]->lname);
			printf("Seat number: %d\n",pointer[m]->seat_number);
		}
	}
}
void show_list_seat(struct airplane * ptr[])
{
	int i;
	puts("Here is the list of empty seats:");
	for(i = 0;i < MAXSEAT;i++)
		if(ptr[i]->seat_reservation == false)
		{
			ptr[i]->fname[0] = '\0'; //Show empty string in the screen
			ptr[i]->lname[0] = '\0';
			printf("First name: %s\n",ptr[i]->fname);
			printf("Last name: %s\n",ptr[i]->lname);
			printf("Seat number: %d\n",ptr[i]->seat_number);
		}
}
void show_number_seat(struct airplane * ptr[])
{
	int i;
	puts("Here is the number of empty seats:");
	for(i = 0;i < MAXSEAT;i++)
		if(ptr[i]->seat_reservation == false)
			printf("%d ",ptr[i]->seat_number);
	putchar('\n');
}
void show_reserved_seat(struct airplane * ptr[])
{
	int i;
	puts("Here is the number of seats which have been reserved:");
	for(i = 0;i < MAXSEAT;i++)
		if(ptr[i]->seat_reservation == true)
			printf("%d ",ptr[i]->seat_number);
	putchar('\n');
}
char get_choice(void)
{
	int ch;
	puts("To choose a function,enter its letter label:");
	puts("a) Show number of empty seats");
	puts("b) Show list of empty seats");
	puts("c) Show alphabetical list of seats");
	puts("d) Assign a customer to a seat assignment");
	puts("e) Delete a seat assignment");
	puts("f) quit");
	ch = get_first();
	while(ch < 'a' || ch > 'f')
	{
		puts("Please enter a,b,c,d,e or f:");
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
int * input(int * n)
{
	while(scanf("%d",n) != 1)
	{
		puts("Please enter again:");
		fflush(stdin);
	}
	while(*n < 1 || *n > 12)
	{
		puts("Please enter seat numbere between 1 and 12.");
		puts("Please enter again:");
		while(scanf("%d",n) != 1)
		{
			puts("Please enter again:");
			fflush(stdin);
		}
	}
	return n;
}
char * s_gets(char * st,int n)
{
	char *ret_val;
	char *find;
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
