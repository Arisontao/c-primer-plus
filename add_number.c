#include <stdio.h>
#include <stdlib.h>
void main() 
{
	int i = 0,qian = 0,hou = 0;//一个运算符连的2个数分别为qian hou
	int ysf = 0;//运算符
	int qh = 0;//当前是qian还是hou的标记 0为qian 1为hou
	int total = 0;//算式结果
	int suan[8] = {0};//8个可能的运算符插入位，0表没有，1表加法，2表减法
	
	for(suan[0] = 0; suan[0] < 3; suan[0]++)//1 2间的运算符
	for(suan[1] = 0; suan[1] < 3; suan[1]++)//2 3间的运算符
	for(suan[2] = 0; suan[2] < 3; suan[2]++)//3 4间的运算符
	for(suan[3] = 0; suan[3] < 3; suan[3]++)//4 5间的运算符
	for(suan[4] = 0; suan[4] < 3; suan[4]++)//5 6间的运算符
	for(suan[5] = 0; suan[5] < 3; suan[5]++)//6 7间的运算符
	for(suan[6] = 0; suan[6] < 3; suan[6]++)//7 8间的运算符
	for(suan[7] = 0; suan[7] < 3; suan[7]++)//8 9间的运算符
	{
	//重置
		qian = 1;//第一个数
		ysf = 0;
		qh = 0;
		total = 0;
		//开始运算
		for(i = 0; i < 8; i++)
		{
			//无运算符
			if(suan[i] == 0)
			{
				if(qh == 0) 
					qian = qian * 10 + (i + 2);
				else 
					hou = hou * 10 + (i + 2);
			}
			//遇到了新运算符
			else{
					//完成前一运算符的计算，结果为qian，依然取hou
					if(qh == 1)
					{
						total = qian + ysf * hou;
						qian = total;
						hou = i + 2;
					}
					//开始取hou数
					else{
						qh = 1;
						hou = i + 2;
					}
					//更新运算符
					if(suan[i] == 1) 
						ysf = 1;
					else 
						ysf = -1;
				}
		}
		//完成最后一个运算
		total = qian + ysf * hou;
		//输出
		if(total == 100)
		{
			for(i = 0; i < 9; i++)
			{
				printf("%d",i+1);
				if(i < 8 && suan[i] == 1) 
					printf("+");
				if(i<8 && suan[i] == 2) 
					printf("-");
			}
			printf("=%d\n",total);
		}
	}
	system("pause");
}