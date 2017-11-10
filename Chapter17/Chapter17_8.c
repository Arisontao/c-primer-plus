#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
//这里写show的时候是对数组的每个元素进行操作的 所以这里得注意
//show应该有两种操作 一种是显示这个节点里面的宠物 一种是显示所有的宠物
void delete_pet(Tree * ptree);
void add_pet(Tree * ptree);
void replace_pet(Tree * ptree);
void show_allpets(Item * array);
void show_pet(Tree * ptree);
int get_choice(void);
int get_first(void);
int get_let(char * st);
char * s_gets(char * st,int n);
int main(void)
{
	Tree pets;
	int choice;

	InitializeTree(&pets);
	while((choice = get_choice()) != 'q')
	{
		switch(choice)
		{
			case 'a': add_pet(&pets); break;
			case 'd': delete_pet(&pets); break;
			case 's': show_pet(&pets); break;
			case 'r': replace_pet(&pets); break;
		}
	}
	puts("Bye!");

	return 0;
}
void replace_pet(Tree * ptree)
{
	Item temp;
	Item temp2;
	puts("Enter the pet name:");
	s_gets(temp.petname,SLEN);
	puts("Enter the pet kind:");
	s_gets(temp.petkind,SLEN);
	puts("Enter the replaced pet name:");
	s_gets(temp2.petname,SLEN);
	puts("Enter the replaced pet kind:");
	s_gets(temp2.petkind,SLEN);
	if(ReplaceItem(ptree,&temp,&temp2))
		puts("Replaced successfully!");
	else
		puts("Replaced failure!");
}
void delete_pet(Tree * ptree)
{
	Item temp;
	puts("Enter the pet name:");
	s_gets(temp.petname,SLEN);
	puts("Enter the pet kind:");
	s_gets(temp.petkind,SLEN);
	if(DeleteItem(ptree,&temp))
		puts("Deletion success!");
	else
		puts("Deletion failure!");
}
void add_pet(Tree * ptree)
{
	Item temp;
	puts("Enter the pet name:");
	s_gets(temp.petname,SLEN);
	puts("Enter the pet kind:");
	s_gets(temp.petkind,SLEN);
	if(AddItem(ptree,&temp))
		puts("Added successfully!");
	else
		puts("Added failure!");
}
void show_allpets(Item * array)
{
	int i;
	for(i = 0;i < SLEN;i++)
		if(array[i].petname[0] != '\0') 
			printf("Petname: %s Petkind: %s\n",array[i].petname,array[i].petkind);
}
void show_pet(Tree * ptree)
{
	char temp[SLEN];

	if(TreeIsEmpty(ptree))
    {
        puts("No entries!");
        return;
    }
	puts("a to show all pets,n to show pets in a node.");
	puts("Enter your choice:");
	if(get_let("an") == 'a')
		Traverse(ptree,show_allpets);
	else
	{
		puts("Enter the node name you want to show:");
		s_gets(temp,SLEN);
		SeekTree(ptree,temp);
	}
}
int get_let(char * st)
{
	int ch;
	ch = get_first();
	while(strchr(st,ch) == NULL)
	{
		printf("Enter a character in %s,pleaese enter again:",st);
		ch = get_first();
	}
	return ch;
}
int get_choice(void)
{
	int ch;
	puts("Please enter the operation you want to do:");
	puts("a)add a pet		d)delete a pet");
	puts("r)replace pet		s)show pet");
	puts("e)seek pet		q)quit");
	ch = get_first();
	while(strchr("adirsq",ch) == NULL)
	{
		puts("Please enter a,d,i,r,s or q:");
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



#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
typedef struct pair
{
	struct trnode * parent;
	struct trnode * child;
}Pair;
static Pair FindParent(char * temp,Trnode * root);
static Trnode * SeekName(Trnode * root,char * temp);
static bool ToLeft(const Item * m,const Item * n);
static bool ToRight(const Item * m,const Item * n);
static void AddNode(Trnode * root,Trnode * new);
static void InOrder(Trnode * root,void(*pfun)(Item * array));
static Trnode * MakeNode(Item * pi);
static void DeleteNode(Trnode ** ptr);
static bool ToRi(char * temp,char * petname);
static bool ToLe(char * temp,char * petname);

void InitializeTree(Tree * ptree)
{
	ptree->root = NULL;
	ptree->size = 0;
}
bool TreeIsFull(const Tree * ptree)
{
	return ptree->size == MAXITEMS;
}
bool TreeIsEmpty(const Tree * ptree)
{
	return ptree->size == 0;
}
int TreeItemCount(const Tree * ptree)
{
	return ptree->size;
}
bool InTree(const Tree * ptree,const Item * pi)
{
	int i;
	Trnode * pnode = SeekName(ptree->root,pi->petname);
	if(pnode == NULL)
		return false;
	else
	{
		for(i = 0;i < SLEN;i++)
			if(strcmp(pnode->pet[i].petkind,pi->petkind) == 0)
				return true;
		return false;
	}
}
void SeekTree(Tree * ptree,char * temp)
{
	//先是查找到这个名字是否在节点中
	//然后在打印 这里打印是调用函数打印吗
	//这个函数没有判断是否存在这个名字的情况 所以便会出现错误
	Trnode * pnode;
	int i;

	if(ptree != NULL)
		pnode = SeekName(ptree->root,temp);
	if(pnode == NULL)
	{
		fprintf(stderr,"There is no dog nameed %s!\n",temp);
		return;
	}
	for(i = 0;i < SLEN;i++)
		if(pnode->pet[i].petname[0] != '\0')
            printf("Petname: %s Petkind: %s\n",pnode->pet[i].petname,pnode->pet[i].petkind);
}
void Traverse(Tree * ptree,void(*pfun)(Item * array)) //这个函数应该改成是接受一个Item类型的数组 这样你才能对每一个元素进行应用
{
	if(ptree != NULL)
        InOrder(ptree->root,pfun);
}
bool AddItem(Tree * ptree,Item * pi)
{
	int i,num;
	Trnode * new_node;
	Trnode * pnode = SeekName(ptree->root,pi->petname);
	//添加项目也是这样  首先如果这个宠物的名字不存在的话 那就创建一个新的节点 并安放这个节点的位置
	//而如果这个宠物的名字存在的话 就得在数组里面添加一个元素了
	if(TreeIsFull(ptree))
	{
		fprintf(stderr,"The tree is full now!\n");
		return false;
	}
	//在添加的时候得注意是否相同
	if(InTree(ptree,pi))
	{
		fprintf(stderr,"The item is in the tree!\n");
		return false;
	}
	if(pnode == NULL)
	{
		new_node = MakeNode(pi); 
		if(new_node == NULL)
		{
			fprintf(stderr,"Error in making new nodes!\n");
			return false;
		}
		if(ptree->root == NULL)
			ptree->root = new_node;
		else
			AddNode(ptree->root,new_node);
		ptree->size++; 
		return true;
	}
	else
	{
		num = 0;
		for(i = 0;i < SLEN;i++)
			if(pnode->pet[i].petname[0] != '\0') 
				num++;
		pnode->pet[num] = *pi; 
		return true;
	}
}
bool ReplaceItem(Tree * ptree,Item * m,Item * n) 
{
	int i;
	int flag = 0;
	int num = 0;

	Trnode * pnode = SeekName(ptree->root,m->petname);
	if(InTree(ptree,m) == false)
	{
		fprintf(stderr,"The item you want to replace isn't in the list!\n");
		return false;
	}
	if(InTree(ptree,n))
	{
		fprintf(stderr,"Error in replacing item!\n");
		return false;
	}
	for(i = 0;i < SLEN;i++)
		if(pnode->pet[i].petname[0] != '\0')
			num++;
    if(num == 1)
    {
        fprintf(stderr,"There is only one item in the node,can't replace it!\n");
        return false;
    }
    else if(num > 1)
    {
        for(i = 0;i < SLEN;i++)
            if(strcmp(pnode->pet[i].petkind,m->petkind) == 0)
            {
                flag = i;
                break;
            }

        pnode->pet[flag] = *n;
        return true;
    }
}
bool DeleteItem(Tree * ptree,Item * pi)
{
	int i;
	int flag = 0;
	int num = 0;
	Trnode * pnode = SeekName(ptree->root,pi->petname);
	Pair look = FindParent(pnode->pet[0].petname,ptree->root); 
	if(InTree(ptree,pi) == false)
	{
		fprintf(stderr,"The item isn't in the tree!\n");
		return false;
	}
	for(i = 0;i < SLEN;i++)
		if(pnode->pet[i].petname[0] != '\0')
			num++;
	if(num == 1)
    {
        if(look.parent == NULL)
			DeleteNode(&ptree->root);
		else if(look.parent->left == look.child)
			DeleteNode(&look.parent->left);
		else
			DeleteNode(&look.parent->right);
		ptree->size--;
		return true;
    }
	else if(num > 1)
    {
        for(i = 0;i < num;i++) 
            if(strcmp(pnode->pet[i].petkind,pi->petkind) == 0 && strcmp(pnode->pet[i].petname,pi->petname) == 0)
                flag = i; 
        for(i = flag + 1;i < num;i++) 
            pnode->pet[i - 1] = pnode->pet[i];
        pnode->pet[num - 1].petname[0] = '\0';
        pnode->pet[num - 1].petkind[0] = '\0';
        return true;
    }
}
static void DeleteNode(Trnode ** ptr)
{
	//删除节点有三种情况
	//1.这个节点没有子树
	//2.有一个子树
	//3.有两个子树
	Trnode * temp;

	if((*ptr)->left == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	}
	else if((*ptr)->right == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}
	else
	{
		for(temp = (*ptr)->left;temp->right != NULL;temp = temp->right)
			continue;
		temp->right = (*ptr)->right;
		temp = (*ptr);
		(*ptr) = (*ptr)->left;
		free(temp);
	}
}
static Trnode * SeekName(Trnode * root,char * temp)
{
	if(root != NULL)
	{
		SeekName(root->left,temp);
		if(strcmp(temp,root->pet[0].petname) == 0)
			return root;
		SeekName(root->right,temp);
	}
}
static void InOrder(Trnode * root,void(*pfun)(Item * array))
{
    if(root != NULL)
    {
        InOrder(root->left,pfun);
        (*pfun)(root->pet);
        InOrder(root->right,pfun);
    }
}
static void AddNode(Trnode * root,Trnode * new)
{
	if(ToLeft(&new->pet[0],&root->pet[0]))
	{
		if(root->left == NULL)
			root->left = new;
		else
			AddNode(root->left,new);
	}
	else if(ToRight(&new->pet[0],&root->pet[0]))
	{
		if(root->right == NULL)
			root->right = new;
		else
			AddNode(root->right,new);
	}
	else
	{
		fprintf(stderr,"location error in AddNode()!\n");
		exit(1);
	}
}
static Trnode * MakeNode(Item * pi)
{
	Trnode * new_node;
	int i;

	new_node = (Trnode *) malloc(sizeof(Trnode));
	if(new_node != NULL)
	{
		new_node->left = NULL;
		new_node->right = NULL;
        for(i = 0;i < SLEN;i++)
            new_node->pet[i].petname[0] = '\0';
		new_node->pet[0] = *pi;
	}
	return new_node;
}
static Pair FindParent(char * temp,Trnode * root)
{
	Pair look;
	look.parent = NULL;
	look.child = root;

	if(look.child == NULL)
		return look;

	while(look.child != NULL)
	{
		if(ToLe(temp,look.child->pet[0].petname))
		{
			look.parent = look.child;
			look.child = look.child->left;
		}
		else if(ToRi(temp,look.child->pet[0].petname))
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		else
			break;
	}
	return look;
}
static bool ToLe(char * temp,char * petname)
{
	if(strcmp(temp,petname) < 0)
		return true;
	else
		return false;
}
static bool ToRi(char * temp,char * petname)
{
	if(strcmp(temp,petname) > 0)
		return true;
	else
		return false;
}
static bool ToLeft(const Item * m,const Item * n)
{
	int comp;
	if((comp = strcmp(m->petname,n->petname)) < 0)
		return true;
	else if(comp == 0 && strcmp(m->petkind,n->petkind) < 0)
		return true;
	else
		return false;
}
static bool ToRight(const Item * m,const Item * n)
{
	int comp;
	if((comp = strcmp(m->petname,n->petname)) > 0)
		return true;
	else if(comp == 0 && strcmp(m->petkind,n->petkind) > 0)
		return true;
	else
		return false;
}



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SLEN 5
#define MAXITEMS 20

typedef struct item
{
	char petname[SLEN];
	char petkind[SLEN];
}Item;

typedef struct trnode
{
	struct trnode * left;
	struct trnode * right;
	Item pet[SLEN];
}Trnode;

typedef struct tree
{
	Trnode * root;
	int size;
}Tree;

void InitializeTree(Tree * ptree);

void Traverse(Tree * ptree,void(*pfun)(Item * array));

bool AddItem(Tree * ptree,Item * pi);

bool TreeIsFull(const Tree * ptree);

bool DeleteItem(Tree * ptree,Item * pi);

bool ReplaceItem(Tree * ptree,Item * m,Item * n);

bool TreeIsEmpty(const Tree * ptree);

bool InTree(const Tree * ptree,const Item * pi);

void SeekTree(Tree * ptree,char * temp);

int TreeItemCount(const Tree * ptree);


