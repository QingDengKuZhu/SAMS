/*************************************
**系统主函数
**************************************/

#include "Data.h"
#include "DataFucntion.h"
#include "FirstMain.h"
#include <stdio.h>
#include <stdlib.h>

int saveflag = 0;		/* 存盘标志,若数据有增,删,改操作,则saveflag变为1 */

int main(void)
{
	PLINK pL = NULL;		/*单链表头指针*/	
	FILE *pf = NULL;		/*文件指针*/
	int select;				/*保存用户选择结果*/
	char ch;				/*保存(y,Y,n, N)*/
	int count = 0;			/*保存文件中的学生信息条数*/
	PNODE p	= NULL;			/*结点指针*/
	PNODE r = NULL;			/*指向尾结点,若链表为空,则等于头指针*/

	
	/*
	**初始化单链表,生成头结点.
	*/
	pL = (PNODE)malloc(sizeof(NODE));
	if (!pL)
	{
		printf("头结点分配失败!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pL->pnext = NULL;
		r = pL;
	}

	/*
	**以追加的方式打开一个二进制文件
	**可读可写,若文件不存在,则创建文
	**件.
	*/
	pf = fopen(FILE_PATH, "ab+");
	if (!pf)
	{
		printf("文件打开错误");
		exit(EXIT_FAILURE);
	}
	

	/*
	**读入数据
	*/
	while (0 == feof(pf))	/*若文件未读到尾部*/
	{
		p = (PNODE)malloc(sizeof(NODE));
		if (!p)
		{
			printf("待复制数据结点生成失败!\n");
			exit(EXIT_FAILURE);
		}
		
		/*
		**一次从文件中读取一条学生记录
		*/
		if ( 1 == fread(p, sizeof(NODE), 1, pf) )
		{
			p->pnext = NULL;
			r->pnext = p;
			r = p;
			++count;	/*文件记录加一*/
		}

	}

	fclose(pf);/*关闭文件*/

	printf("文件成功打开,当前记录共%d条\n", count);
	getchar();		/*避免上述信息一闪而过*/
	

	while (1)	/* while_@ */
	{
		system("cls");	/*清屏*/
		Menu();			/*显示菜单,供用户选择*/

		p = r;
		printf("\n				请输入你的选择(0~9)			\n");
		scanf("%d", &select);

		if ( 0 == select)
		{
			/**
			若对链表的数据有修改且未进行存盘操作,则标志saveflag为1.
			**/
			if (1 == saveflag)
			{
				getchar();//清除回车
				printf("是否保存数据(Y|N)?");
				scanf("%c", &ch);
				if (ch=='Y'||ch=='y')
				{
					Save(pL);
				}
			}
			printf("谢谢使用!\n");
			getchar();
			break;/*跳出while_@循环*/
		}
		else
		{
			switch (select)
			{
			case 1:					/*增加学生记录*/
				Add(pL);			
				break;
			case 2:					/*删除学生记录*/
				Del(pL);
				break;
			case 3:					/*查询学生记录*/
				Qur(pL);
				break;
			case 4:					/*修改学生记录*/
				Modify(pL);
				break;
			case 5:					/*插入学生记录*/
				Insert(pL);
				break;
			case 6:					/*统计学生记录*/
				Tongji(pL);
				break;
			case 7:					/*对学生记录排序*/
				Sort(pL);
				break;
			case 8:					/*保存学生记录*/
				Save(pL);
				break;
			case 9:					/*显示学生记录*/
				system("cls");
				Disp(pL);
				break;
			default:				/*按键值有误时处理办法*/
				Wrong();
				getchar();
				break;/* 跳出while_@循环 */
			}
		}
	}/* while_@ */


	return EXIT_SUCCESS;
}