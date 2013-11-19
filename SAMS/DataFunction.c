/*************************************
**与系统有关的函数的定义
**************************************/

#include "Data.h"
#include "DataFucntion.h"
#include <windows.h>
#include <conio.h>	/*定义cprintf函数*/
#include <stdio.h>

void PrintHeader(void)
{
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);

	
	return;
}

void PrintData(PNODE p)
{
	printf(FORMAT, DATA);
	return;

}

unsigned int NumberInput(char notice[])
{
	unsigned  t; /*临时保存输入的数据*/
	
	do
	{
		printf(notice);		/*显示提示*/
		scanf("%d", &t);	/*输入分数*/

		/*
		**判断分数是否在合理范围内
		*/
		if ( t>100 || t<0 )
		{
			printf("\n 分数需要在[0,100]范围内!!!\n");
		}
	}while ( t>100 || t<0 );

	return t;
}

void Menu(void)
{
	system("cls");
	gotoxy(10, 5);			/*在文本窗口中设置光标*/
	cprintf("		The Students' Grade Management System\n");
	gotoxy(10, 8);
	cprintf("-------------------------------Menu-------------------------------\n");
	gotoxy(10, 9);
	cprintf("|	1 input   record			2 delete record	   |\n");
	gotoxy(10, 10);
	cprintf("|	3 search  record			4 modify record	   |\n");
	gotoxy(10, 11);
	cprintf("|	5 insert  record			6 count  record	   |\n");
	gotoxy(10, 12);
	cprintf("|	7 sort	  record			8 save   record	   |\n");
	gotoxy(10, 13);
	cprintf("|	9 display record			0 quit   record	   |\n");
	gotoxy(10, 14);
	cprintf("-------------------------------------------------------------------\n");
	
	return;
}

void gotoxy(short x, short y)
{
	COORD pos;	/*COORD在windws.h中定义*/
	pos.X = x; 
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); /* 设置光标位置 */
	
	return;
}

void Wrong(void)
{
	printf("\n\n\n\n\------------------Error:输入数据有误!	请按任意键从新开始----------- \n");
	getchar();
	return;

}

void Add(PLINK pL)
{
	extern int saveflag;	/*判断链表数据是否被修改(增,删, 改),若被修改则saveflag为1,否者为0*/
	PNODE p, r, s;
	char ch;
	char ID[10];
	int flag = 0;			/*重复数组标志位,若输入的ID已经存在,则flag置为1*/
	
	
	r = pL;
	s =pL->pnext;			/*因为单链表一定存在,所以pL一定不为NULL*/
	system("cls");

	while(r->pnext)
	{
		r = r->pnext;		/*将指针移至于链表最末尾，准备添加记录*/
	}/*r指向最后一个有效结点,若DAN	单链表为空,则指向头结点*/

	/*
	**一次可输入多条记录，直至输入学号为0的记录结点添加操作
	*/
	while (1)	/*while_@*/
	{
		while (1)	/*while_#*/
		{
			StringInput(ID, 10, "input number(press 0 return mune):");/*格式化输入学号并检验*/
			flag = 0;
		
			/*
			**若输入0,则返回.
			*/
			if ( 0 == strcmp(ID, "0"))
			{
				return;	/*返回主菜单*/
			}
			
			/*
			**判断输入的ID是否已经存在
			*/
			s = pL->pnext;
			while (s)/*while_!*/
			{
				if ( 0 == strcmp(s->data.ID, ID) )
				{
					flag = 1;	/*若已存在,则flag置为1*/
					break;
				}
				s = s->pnext;
			}/*while_!*/

			if ( flag == 1 )
			{
				getchar();
				printf("ID:%s已存在,需要重新输入吗?(Y/N)", ID);
				scanf("%c", &ch);
				if ( 'y'==ch || 'Y'== ch )
				{
					continue;	/*返回到while_#*/
				}
				else
				{
					return;
				}
			}
			else
			{
				break;
			}
		} /*while_#*/

		p = (PNODE)malloc(sizeof(NODE));
		if (!p)
		{
			printf("动态内存分配失败!\n");
			return;	/*返回主界面*/
		}
		strcpy(p->data.ID, ID);
		StringInput(p->data.name, 15, "Name:");
	
		p->data.cgrade = NumberInput("C language Score[0-100]:"); /*输入并检验分数，分数必须在0－100之间*/
		p->data.mgrade = NumberInput("Math Score[0-100]:");   /*输入并检验分数，分数必须在0－100之间*/
		p->data.egrade = NumberInput("English Score[0-100]:"); /*输入并检验分数，分数必须在0－100之间*/
		p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade; /*计算总分*/
		p->data.ave=(p->data.total/3);  /*计算平均分*/
		p->data.mingci=0;
		
		p->pnext=NULL; /*表明这是链表的尾部结点*/
		r->pnext=p;  /*将新建的结点加入链表尾部中*/
		r=p;/*r指向最后一个有效结点*/
		
		saveflag=1;
	}	/*while_@*/

	return;
}

void StringInput(char Buffer[], size_t lens, char notice[])
{
	char n[255];
	do 
	{
		printf(notice);			/*显示提示信息*/
		scanf("%s", n);			/*输入字符串*/
		/*进行长度校验,当输入字符串超过lens时,从新输入*/
		if ((int)strlen(n)>lens)	/*strlen返回为size_t类型*/
		{
			printf("\n exceed the required length!	\n");
		}
	} while ((int)strlen(n) > lens);
	
	strcpy(Buffer, n);/*将输入的字符串复制到字符串Buffer中*/
	return;	
}

void Del(PLINK pL)
{
	extern int saveflag;
	int select;
	PNODE p;
	PNODE r;	/*r指向被删除结点前一个结点*/
	char findmess[20];
	
	if (!pL->pnext)
	{
		system("cls");
		printf("\n没有学生记录\n");
		getchar();
		return;
	}
	
	system("cls");
	
	printf("\n  ====>标号1:Delete by number      ======> 标号2:delete by name");
	printf("please choice [1,2]:");
	scanf("%d", &select);
	if ( 1 == select)
	{
		StringInput(findmess, 10, "input the existing student number:");
		p = Locate(pL, findmess, "ID");
		if (p)
		{
			r = pL;
			while (p != r->pnext)
			{
				r = r->pnext;
			}
			r->pnext = p->pnext;
			free(p);
			printf("\n==========>删除成功!\n");
			getchar();
			saveflag = 1;
		}
		else
		{
			Nofind();
		}
		getchar();
	}
	else if (select == 2)
	{
		StringInput(findmess, 15, "input the existing student name");
		p = Locate(pL, findmess, "name");
		if (p)
		{
			r = pL;
			while ( p != r->pnext)
			{
				r = r->pnext;
			}
			r->pnext = p->pnext;
			free(p);
			printf("\n=====>删除成功!\n");
			getchar();
			saveflag = 1;
		}
		else
		{
			Nofind();
			getchar();
		}
		
	}
	else
	{
		Wrong();
		getchar();
	}
	
	
	getchar();
	return;
}

void Nofind(void)  
{
	printf("\n没有找到该学生信息!\n");
	return;
}

void Disp(PNODE pL)  /*显示单链表l中存储的学生记录，内容为student结构中定义的内容*/
{
	PNODE p = pL->pnext;
	if (!p)
	{
		printf("\n====>没有学生记录!\n");
		getchar();		
	}
	else
	{
		printf("\n\n");
		PrintHeader();		/*输出表格头部*/

		while(p)
		{
			PrintData(p);
			printf(HEADER3);
			p = p->pnext;
		}
		getchar();
	}
	
	getchar();	/*在每个return前要加上一个getchar()语句,否者会一闪而过*/
	return;

	
}

NODE *Locate(PLINK pL, char findmess[], char nameornum[])
{
	PNODE r = NULL;
	/**
	按编号查询
	**/
	if ( 0 == strcmp(nameornum, "ID") )
	{
		r = pL->pnext;
		while (r)
		{
			if ( 0 == strcmp(r->data.ID, findmess) )
			{
				return  r;
			}
			r = r->pnext;
		}
	}
	/**
	按照姓名查询
	**/
	else if ( 0 == strcmp(nameornum, "name") )
	{
		r = pL->pnext;
		while (r)
		{
			if ( 0 == strcmp(r->data.name, findmess) )
			{
				return r;
			}
			r = r->pnext;
		}
	}
	
	return NULL;
}

void Qur(PLINK pL)
{
	int select; /*1:按照学号查找,2:按照姓名查找,其他,返回主界面(菜单)*/
	char searchinput[20];
	PNODE p = NULL;
	if (!pL->pnext)
	{
		system("cls");
		printf("\n=====>No student record!\n");
		getchar();
		return;
	}
	system("cls");
	printf("\n    =====>1 Search by number  =====>2 Search by name\n");
	scanf("%d", &select);
	if ( 1 == select )
	{
		StringInput(searchinput, 10, "input the existing student number:");
		p = Locate(pL, searchinput, "num");
		if (p)
		{
			PrintHeader();
			PrintData(p);
			printf(END);
			printf("按任意键返回");
			getchar();
		}
		else
		{
			Nofind();
		}
		getchar();
	}
	else if ( 2 == select)
	{
		StringInput(searchinput, 15, "input the existing student name:");
		p = Locate(pL, searchinput, "name");
		if (p)
		{
			PrintHeader();
			PrintData(p);
			printf(END);
			printf("press any key to return");
			getchar();
		}
		else
		{
			Nofind();
		}
		getchar();
	}
	else
	{
		Wrong();
	}
	getchar();
	
	return;
}

void Modify(PLINK pL)
{
	extern int saveflag;
	PNODE p = NULL;
	char findmess[20];
	if ( !pL->pnext )
	{
		system("cls");
		printf("\n没有学生记录\n");
		getchar();
		return;
	}
	system("cls");
	printf("修改学生分数");
	
	StringInput(findmess,10,"input the existing student number:"); /*输入并检验该学号*/
	p=Locate(pL,findmess,"num"); /*查询到该节点*/
	if(p) /*若p!=NULL,表明已经找到该节点*/
	{
		printf("Number:%s,\n",p->data.ID);
		printf("Name:%s,",p->data.name);
		StringInput(p->data.name,15,"input new name:");
		
		printf("C language score:%d,",p->data.cgrade);
		p->data.cgrade=NumberInput("C language Score[0-100]:");
		
		printf("Math score:%d,",p->data.mgrade);
		p->data.mgrade=NumberInput("Math Score[0-100]:");
		
		
		printf("English score:%d,",p->data.egrade);
		p->data.egrade=NumberInput("English Score[0-100]:");
		
		p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade;
		p->data.ave=(float)(p->data.total/3);
		p->data.mingci=0;
		printf("\n修改成功!\n");
		saveflag=1;
	}
	else
	{
		Nofind();
		getchar();
	}
	getchar();
	
	return;
}

void Insert(PLINK pL)
{
	extern int saveflag;
	PNODE p,v,newinfo; /*p指向插入位置，newinfo指新插入记录*/
	char ch,num[10],s[10];  /*s[]保存插入点位置之前的学号,num[]保存输入的新记录的学号*/
	int flag=0;
	v=pL->pnext;
	system("cls");
	Disp(pL);
	while(1)
	{
		StringInput(s,10,"please input insert location  after the Number:");
		flag=0;
		v=pL->pnext;
		while(v) /*查询该学号是否存在，flag=1表示该学号存在*/
		{
			if(strcmp(v->data.ID, s)==0)  {flag=1;break;}
			v=v->pnext;
		}
		if(flag==1)
		{
			break; /*若学号存在，则进行插入之前的新记录的输入操作*/
		}
		else
		{  
			getchar();
			printf("\n=====>The number %s is not existing,try again?(y/n):",s);
			scanf("%c",&ch);
			if(ch=='y'||ch=='Y')
			{
				continue;
			}
			else
			{
				return;
			}
		}
	}
	/*以下新记录的输入操作与Add()相同*/
	StringInput(num,10,"input new student Number:");
	v=pL->pnext;
	while(v)
	{
		if(strcmp(v->data.ID,num)==0)
		{
			printf("=====>Sorry,the new number:'%s' is existing !\n",num);
			PrintHeader();
			PrintData(v);
			printf("\n");
			getchar();
			return;
		}
		v=v->pnext;
	}
	
	
	newinfo=(PNODE)malloc(sizeof(NODE));
	if(!newinfo)
	{
		printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
		return ;             /*返回主界面*/
	}
	strcpy(newinfo->data.ID,num);
	StringInput(newinfo->data.name,15,"Name:");
	newinfo->data.cgrade=NumberInput("C language Score[0-100]:");
	newinfo->data.mgrade=NumberInput("Math Score[0-100]:");
	newinfo->data.egrade=NumberInput("English Score[0-100]:");
	newinfo->data.total=newinfo->data.egrade+newinfo->data.cgrade+newinfo->data.mgrade;
	newinfo->data.ave=(float)(newinfo->data.total/3);
	newinfo->data.mingci=0;
	newinfo->pnext=NULL;
	saveflag=1; /*在main()有对该全局变量的判断，若为1,则进行存盘操作*/
	/*将指针赋值给p,因为l中的头节点的下一个节点才实际保存着学生的记录*/
	p=pL->pnext;
	while(1)
	{
		if(strcmp(p->data.ID,s)==0) /*在链表中插入一个节点*/
		{
			newinfo->pnext=p->pnext;
			p->pnext=newinfo;
			break;
		}
		p=p->pnext;
	}
	
	Disp(pL);
	printf("\n\n");
	getchar();
	
	return;
}

void Tongji(PLINK pL)
{
	
	PNODE pm,pe,pc,pt; /*用于指向分数最高的节点*/
	PNODE r=pL->pnext;
	int countc=0,countm=0,counte=0; /*保存三门成绩中不及格的人数*/
	if(!r)
	{
		system("cls");
		printf("\n=====>Not student record!\n");
		getchar();
		return ;
	}
	system("cls");
	Disp(pL);
	pm=pe=pc=pt=r;
	while(r)
	{
		if(r->data.cgrade<60) 
		{
			countc++;
		}
		if(r->data.mgrade<60)
		{
			countm++;
		}
		if(r->data.egrade<60)
		{
			counte++;
		}
		
		if(r->data.cgrade>=pc->data.cgrade)   
		{
			pc=r;
		}
		if(r->data.mgrade>=pm->data.mgrade)    
		{
			pm=r;
		}
		if(r->data.egrade>=pe->data.egrade)    
		{
			pe=r;
		}
		if(r->data.total>=pt->data.total)
		{
			pt=r;
		}
		
		r=r->pnext;
	}
	
	printf("\n------------------------------统计结果--------------------------------\n");
	printf("C语言成绩<60:%d (人)\n",countc);
	printf("数学成绩  <60:%d (人)\n",countm);
	printf("英语成绩   <60:%d (人)\n",counte);
	printf("-------------------------------------------------------------------------------\n");
	printf("The highest student by total   scroe   name:%s totoal score:%d\n",pt->data.name,pt->data.total);
	printf("The highest student by English score   name:%s totoal score:%d\n",pe->data.name,pe->data.egrade);
	printf("The highest student by Math    score   name:%s totoal score:%d\n",pm->data.name,pm->data.mgrade);
	printf("The highest student by C       score   name:%s totoal score:%d\n",pc->data.name,pc->data.cgrade);
	printf("\n\npress any key to return");
	getchar();
	return;
}

void Sort(PLINK pL)
{
	extern int saveflag;
	PNODE ll;
	PNODE p,rr,s;
	int i=0;
	if(pL->pnext==NULL)
	{
		system("cls");
		printf("\n=====>Not student record!\n");
		getchar();
		return ;
	}

	ll=(PNODE)malloc(sizeof(NODE)); /*用于创建新的节点*/
	if(!ll)
	{
		printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
		return ;             /*返回主界面*/
	}
	ll->pnext=NULL;
	system("cls");
	p=pL->pnext;
	while(p) /*p!=NULL*/
	{
		s=(PNODE)malloc(sizeof(NODE)); /*新建节点用于保存从原链表中取出的节点信息*/
		if(!s) /*s==NULL*/
		{
			printf("\n allocate memory failure "); /*如没有申请到，打印提示信息*/
			return ;             /*返回主界面*/
		}
		s->data=p->data; /*填数据域*/
		s->pnext=NULL;    /*指针域为空*/
		rr=ll;
		/*rr链表于存储插入单个节点后保持排序的链表，ll是这个链表的头指针,每次从头开始查找插入位置*/

		while(rr->pnext!=NULL && rr->pnext->data.total>=p->data.total)
		{
			rr=rr->pnext;/*指针移至总分比p所指的节点的总分小的节点位置*/
		} 
		if(rr->pnext==NULL)/*若新链表ll中的所有节点的总分值都比p->data.total大时，就将p所指节点加入链表尾部*/
		{
			rr->pnext=s;
		}
		else /*否则将该节点插入至第一个总分字段比它小的节点的前面*/
		{
			s->pnext=rr->pnext;
			rr->pnext=s;
		}
		p=p->pnext; /*原链表中的指针下移一个节点*/
	}

	pL->pnext=ll->pnext; /*ll中存储是的已排序的链表的头指针*/
	p=pL->pnext;           /*已排好序的头指针赋给p，准备填写名次*/
	while(p!=NULL)  /*当p不为空时，进行下列操作*/
	{
		i++;       /*结点序号*/
		p->data.mingci=i;   /*将名次赋值*/
		p=p->pnext;   /*指针后移*/

	}
	saveflag=1;
	printf("\n    =====>sort complete!\n");
	
	return;
}

void Save(PLINK pL)
{
	extern int saveflag;
	FILE* fp;
	PNODE p;
	int count=0;
	fp=fopen(FILE_PATH,"wb");/*以只写方式打开二进制文件*/
	if(fp==NULL) /*打开文件失败*/
	{
		printf("\n=====>文件打开错误!\n");
		getchar();
		return ;
	}
	
	p=pL->pnext;

	while(p)
	{
		if(fwrite(p,sizeof(NODE),1,fp)==1)/*每次写一条记录或一个节点信息至文件*/
		{ 
			p=p->pnext;
			count++;
		}
		else
		{
			break;
		}
	}
	if(count>0)
	{
		getchar();
		printf("\n\n\n\n\n=====>save file complete,total saved's record number is:%d\n",count);
		getchar();
		saveflag=0;
	}
	else
	{
		system("cls");
		printf("the current link is empty,no student record is saved!\n");
		getchar();
	}
	fclose(fp); /*关闭此文件*/
}



