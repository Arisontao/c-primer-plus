#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXNAME 40
#define MAXSEAT 12
#define FLIGHT 4
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
char get_choice_flight(void);
int get_answer(char *st);
void show_reserved_seat(struct airplane * ptr[]);
void show_number_seat(struct airplane * ptr[]);
void show_list_seat(struct airplane * ptr[]);
void show_alpha_seat(struct airplane * ptr[]);
void assign_seat(struct airplane * ptr[]);
void delete_seat(struct airplane * ptr[]); 
char confirm_seat(struct airplane * ptr[],int n);
void flight(char ch,struct airplane * ptr[]);
int main(void)
{
	struct airplane seat[FLIGHT][MAXSEAT]; 
	struct airplane *pointer[FLIGHT][MAXSEAT];
	FILE * fp;
	size_t size = sizeof(struct airplane);
	int i,j;
	int choice;
	int m;

	for(i = 0;i < FLIGHT;i++)
	{
		for(j = 0;j < MAXSEAT;j++)
		{
			pointer[i][j] = &seat[i][j]; 
			pointer[i][j]->seat_number = j + 1;
			pointer[i][j]->seat_reservation = false;
		}
	}
	if((fp = fopen("airplane.dat","rb")) == NULL)
	{
		for(i = 0;i < FLIGHT;i++)
        {
            for(j = 0;j < MAXSEAT;j++)
            {
                seat[i][j].seat_number = j + 1;
                seat[i][j].seat_reservation = false;
            }
        }
	}
	else
	{
		for(m = 0;m < FLIGHT;m++)
			fread(seat[m],size,MAXSEAT,fp);
		fclose(fp);
	}
	while((choice = get_choice_flight()) != 'e')
	{
		switch(choice)
		{
			case 'a':	flight('a',pointer[0]);
				break;
			case 'b':	flight('b',pointer[1]);
				break;
			case 'c':	flight('c',pointer[2]);
				break;
			case 'd':	flight('d',pointer[3]);
				break;
		}
	}
	if((fp = fopen("airplane.dat", "wb")) == NULL )
		puts("Can't save data to file.");
	else
	{
		for(m = 0;m < FLIGHT;m++)
			fwrite(seat[m],size,MAXSEAT,fp);
		fclose(fp);
	}
	puts("Bye from Colossus Airlines!");

	return 0;
}
void flight(char ch,struct airplane *ptr[])
{
	int character;
	int num; 

	if(ch == 'a') 
	{
		puts("This is the 102 flight,please enter your choice:");
		num = 102;
	}
	else if(ch == 'b')
	{
		puts("This is the 311 flight,please enter your choice:");
		num = 311;
	}
	else if(ch == 'c')
	{
		puts("This is the 444 flight,please enter your choice:");
		num = 444;
	}
	else if(ch == 'd')
	{
		puts("This is the 519 flight,please entr your choice:");
		num = 519;
	}
	while((character = get_choice()) != 'g') 
	{
		switch(character) 
		{
			case 'a':	show_number_seat(ptr);
				break;
			case 'b':	show_list_seat(ptr);
				break;
			case 'c':	show_alpha_seat(ptr);
				break;
			case 'd':	assign_seat(ptr);
				break;
			case 'e':	delete_seat(ptr);
				break;
			case 'f':	if(confirm_seat(ptr,num) == 'n') 
							break;
						else
							return;
		}
	}
}
char get_choice_flight(void)
{
	int ch;
	puts("This airplane has four flight everyday,please choose the flight you want to take:");
	puts("a) flight 102		b) flight 311");
	puts("c) flight 444		d) flight 519");
	puts("e) quit");
	ch = get_first();
	while(ch < 'a' || ch > 'e')
	{
		puts("Please enter a,b,c,d or e:");
		ch = get_first();
	}
	return ch;
}
char confirm_seat(struct airplane * ptr[],int n) 
{
	int i;
	int flag;
	char ch; 

	flag = 0;
	for(i = 0;i < MAXSEAT;i++) 
		if(ptr[i]->seat_reservation == false)
			flag++;
	if(flag == MAXSEAT)
	{
		puts("There are no seats have been reserved.");
		puts("Validation failure.");
		return 0;
	}
	printf("For flight %d,you have reserved the followed seats:",n);
	for(i = 0;i < MAXSEAT;i++)
		if(ptr[i]->seat_reservation == true)
			printf(" %d ",i + 1);
	putchar('\n');
	puts("Do you really want to book these seats?<y/n>");
	if(get_answer("yn") == 'n')
	{
		ch = 'n';
		for(i = 0;i < MAXSEAT;i++)
			ptr[i]->seat_reservation = false; 
		puts("Please choose your seats again:");
		return ch;
	}
	else
	{
		ch = 'y';
		printf("You have successfully booked %d seats for flight %d\n",MAXSEAT - flag,n);
		puts("Here are your seats:");
		for(i = 0;i < MAXSEAT;i++)
		if(ptr[i]->seat_reservation == true)
			printf(" %d ",i + 1);
		putchar('\n');
		return ch;
	}
}
int get_answer(char *st)
{
	int ch;
	ch = get_first();
	while(strchr(st,ch) == NULL)
	{
		printf("Please enter a character in the list %s\n",st);
		ch = get_first();
	}
	return ch;
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
							puts("Deletion failed."); 
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
						while(pointer2[seatnum - 1].seat_reservation == false) 
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
						while(getchar() != '\n') 
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
		while(getchar() != '\n')
			continue;
		strcpy(ptr[*p - 1]->fname,name);
		puts("Enter the customer last name:");
		s_gets(ptr[*p - 1]->lname,MAXNAME);
		ptr[*p - 1]->seat_reservation = true;
	}
}
void show_alpha_seat(struct airplane * ptr[])
{
	int i,j;
	struct airplane * pointer[MAXSEAT];
	struct airplane * temp;
	char name[MAXSEAT][2 * MAXNAME];
	char temp_name[2 * MAXNAME];
	int m,n;
	int flag = 0; 

	for(n = 0;n < MAXSEAT;n++)
    {
		pointer[n] = ptr[n];
		if(pointer[n]->seat_reservation == true)
		{
			name[n][0] = '\0';
			strncat(name[n],pointer[n]->fname,MAXNAME);
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
			if(name[i][0] != '\0' && name[j][0] != '\0')
			{
				if(strcmp(name[i],name[j]) > 0)
				{
					temp = pointer[i];
					pointer[i] = pointer[j];
					pointer[j] = temp;
					strcpy(temp_name,name[i]);
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
			ptr[i]->fname[0] = '\0';
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
	puts("f) Confirm your seats");
	puts("g) quit");
	ch = get_first();
	while(ch < 'a' || ch > 'g')
	{
		puts("Please enter a,b,c,d,e,f or g:");
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