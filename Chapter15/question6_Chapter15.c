#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
#define MASK
struct fonts_str{
		unsigned long id	: 8;
		unsigned long size	: 7;
		unsigned long align	: 2;
		unsigned long bold	: 1;
		unsigned long italic: 1;
		unsigned long under	: 1;
	};
void show_fonts(struct fonts_str * ptr);
void change_font(struct fonts_str * ptr);
void change_align(struct fonts_str * ptr);
void change_size(struct fonts_str * ptr);
void toggle_bold(struct fonts_str * ptr);
void toggle_italic(struct fonts_str * ptr);
void toggle_under(struct fonts_str * ptr);
char get_choice(void);
char get_first(void);
const char align_arr[3][MAX] = {"left","center","right"};
const char bold_arr[2][MAX] = {"off","on"};
const char italic_arr[2][MAX] = {"off","on"};
const char under_arr[2][MAX] = {"off","on"};
const static char size = CHAR_BIT * sizeof(int);
int main(void)
{
	struct fonts_str fonts = {1,12,0,0,0,0};
	int choice;

	puts("Original settings:");
	show_fonts(&fonts);
	while((choice = get_choice()) != 'q')
	{
		switch(choice)
		{
			case 'f':	change_font(&fonts);
				break;
			case 's':	change_size(&fonts);
				break;
			case 'a':	change_align(&fonts);
				break;
			case 'b':	toggle_bold(&fonts);
				break;
			case 'i':	toggle_italic(&fonts);
				break;
			case 'u':	toggle_under(&fonts);
				break;
		}
	}

	return 0;
}
void toggle_bold(struct fonts_str * ptr)
{
	ptr->bold = ~(ptr->bold);
	putchar('\n');
	show_fonts(ptr);
}
void toggle_italic(struct fonts_str * ptr)
{
	ptr->italic = ~(ptr->italic);
	putchar('\n');
	show_fonts(ptr);
}
void toggle_under(struct fonts_str * ptr)
{
	ptr->under = ~(ptr->under);
	putchar('\n');
	show_fonts(ptr);
}
void change_font(struct fonts_str * ptr)
{
	int num;
	int i;
	printf("Enter font size(0-255): ");
	while(scanf("%d",&num) != 1 || num < 0 || num > 255)
	{
		puts("Please enter again:");
		fflush(stdin);
	}
	while(getchar() != '\n')
		continue;
	for(i = 0;i < size;i++,num >>= 1)
		ptr->id = num & MASK;
	putchar('\n');
	show_fonts(ptr);
}
void change_size(struct fonts_str * ptr)
{
	int num;
	int i;
	printf("Enter font size(0-127): ");
	while(scanf("%d",&num) != 1 || num < 0 || num > 127)
	{
		puts("Please enter again:");
		fflush(stdin);
	}
	while(getchar() != '\n')
		continue;
	for(i = 0;i < size;i++,num >>= 1)
		ptr->size = num & MASK;
	putchar('\n');
	show_fonts(ptr);
}
void change_align(struct fonts_str * ptr)
{
	int ch;
	puts("Select alignment:");
	puts("l)left	c)center	r)right");
	ch = getchar();
	while(getchar() != '\n')
		continue;
	while(ch != 'l' && ch != 'c' && ch != 'r')
	{
		puts("Please enter l,c or r:");
		ch = getchar();
		while(getchar() != '\n')
			continue;
	}
	switch(ch)
	{
		case 'l':	ptr->align = 0;
			break;
		case 'c':	ptr->align = 1;
			break;
		case 'r':	ptr->align = 2;
			break;
	}
	putchar('\n');
	show_fonts(ptr);
}
void show_fonts(struct fonts_str * ptr)
{
	puts("  ID SIZE ALIGNMENT   B   I   U");
	printf("  %ld   %ld    %s     %s %s %s\n",ptr->id,ptr->size,align_arr[ptr->align],bold_arr[ptr->bold],italic_arr[ptr->italic],under_arr[ptr->under]);
}
char get_choice(void)
{
	int ch;
	puts("f)change font		s)change size	a)change alignment");
	puts("b)toggle bold		i)toggle italic	u)toggle underline");
	puts("q)quit");
	ch = get_first();
	while(ch != 'f' && ch != 's' && ch != 'a' && ch != 'b' && ch != 'i' && ch != 'u' && ch != 'q')
	{
		puts("Please enter f,s,a,b,i,u or q:");
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