#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//先写用递归来逆序显示电影的 再来写别的
#define SLEN 20
typedef struct node
{
	int rating;
	char name[SLEN];
	struct node * next; 
}Node;

void show_reverse();
char * s_gets(char * st,int n);
int main(void)
{
	char temp[SLEN];
	struct Node * head = NULL;
	struct Node * current,*prev;
	
	puts("Enter the movie title:");
	while(s_gets(temp,SLEN) != NULL && temp[0] != '\0') //这里还得判断是否是第一个的时候
	{
		//制造一个链表步骤
		//先分配空间
		//然后在设置指向
		current = (Node *) malloc(sizeof(Node));
		if(head == NULL)
			head = current;
		else
			prev->next = current;
		current->next = NULL;
		strcpy(current->name,temp);
		puts("Enter the movie rating:");
		scanf("%d",&current->rating);
		while(getchar() != '\n')
			continue;
		puts("Enter the next movie title:");
		prev = current;
	}
	if(head == NULL)
		printf("There is no data entered!\n");
	else
	{
		current = head;
		while(current != NULL)
		{
			printf("Movie: %s Rating: %d\n",current->title,current->rating);
			current = current->next;
		}
	}
	show_reverse(head);
	current = head;
	while(current != NULL)
	{
		current = head;
		head = current->next;
		free(current);
	}
	
	return 0;
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
void show_reverse(Node * plist)
{
	if(plist->next != NULL) //这是找到末尾
		show_reverse(plist->next);
	printf("Movie: %s Rating: %d\n",plist->title,plist->rating);
}