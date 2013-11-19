/*************************************
**��ϵͳ�йصĺ����Ķ���
**************************************/

#include "Data.h"
#include "DataFucntion.h"
#include <windows.h>
#include <conio.h>	/*����cprintf����*/
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
	unsigned  t; /*��ʱ�������������*/
	
	do
	{
		printf(notice);		/*��ʾ��ʾ*/
		scanf("%d", &t);	/*�������*/

		/*
		**�жϷ����Ƿ��ں���Χ��
		*/
		if ( t>100 || t<0 )
		{
			printf("\n ������Ҫ��[0,100]��Χ��!!!\n");
		}
	}while ( t>100 || t<0 );

	return t;
}

void Menu(void)
{
	system("cls");
	gotoxy(10, 5);			/*���ı����������ù��*/
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
	COORD pos;	/*COORD��windws.h�ж���*/
	pos.X = x; 
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); /* ���ù��λ�� */
	
	return;
}

void Wrong(void)
{
	printf("\n\n\n\n\------------------Error:������������!	�밴��������¿�ʼ----------- \n");
	getchar();
	return;

}

void Add(PLINK pL)
{
	extern int saveflag;	/*�ж����������Ƿ��޸�(��,ɾ, ��),�����޸���saveflagΪ1,����Ϊ0*/
	PNODE p, r, s;
	char ch;
	char ID[10];
	int flag = 0;			/*�ظ������־λ,�������ID�Ѿ�����,��flag��Ϊ1*/
	
	
	r = pL;
	s =pL->pnext;			/*��Ϊ������һ������,����pLһ����ΪNULL*/
	system("cls");

	while(r->pnext)
	{
		r = r->pnext;		/*��ָ��������������ĩβ��׼����Ӽ�¼*/
	}/*rָ�����һ����Ч���,��DAN	������Ϊ��,��ָ��ͷ���*/

	/*
	**һ�ο����������¼��ֱ������ѧ��Ϊ0�ļ�¼�����Ӳ���
	*/
	while (1)	/*while_@*/
	{
		while (1)	/*while_#*/
		{
			StringInput(ID, 10, "input number(press 0 return mune):");/*��ʽ������ѧ�Ų�����*/
			flag = 0;
		
			/*
			**������0,�򷵻�.
			*/
			if ( 0 == strcmp(ID, "0"))
			{
				return;	/*�������˵�*/
			}
			
			/*
			**�ж������ID�Ƿ��Ѿ�����
			*/
			s = pL->pnext;
			while (s)/*while_!*/
			{
				if ( 0 == strcmp(s->data.ID, ID) )
				{
					flag = 1;	/*���Ѵ���,��flag��Ϊ1*/
					break;
				}
				s = s->pnext;
			}/*while_!*/

			if ( flag == 1 )
			{
				getchar();
				printf("ID:%s�Ѵ���,��Ҫ����������?(Y/N)", ID);
				scanf("%c", &ch);
				if ( 'y'==ch || 'Y'== ch )
				{
					continue;	/*���ص�while_#*/
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
			printf("��̬�ڴ����ʧ��!\n");
			return;	/*����������*/
		}
		strcpy(p->data.ID, ID);
		StringInput(p->data.name, 15, "Name:");
	
		p->data.cgrade = NumberInput("C language Score[0-100]:"); /*���벢�������������������0��100֮��*/
		p->data.mgrade = NumberInput("Math Score[0-100]:");   /*���벢�������������������0��100֮��*/
		p->data.egrade = NumberInput("English Score[0-100]:"); /*���벢�������������������0��100֮��*/
		p->data.total=p->data.egrade+p->data.cgrade+p->data.mgrade; /*�����ܷ�*/
		p->data.ave=(p->data.total/3);  /*����ƽ����*/
		p->data.mingci=0;
		
		p->pnext=NULL; /*�������������β�����*/
		r->pnext=p;  /*���½��Ľ���������β����*/
		r=p;/*rָ�����һ����Ч���*/
		
		saveflag=1;
	}	/*while_@*/

	return;
}

void StringInput(char Buffer[], size_t lens, char notice[])
{
	char n[255];
	do 
	{
		printf(notice);			/*��ʾ��ʾ��Ϣ*/
		scanf("%s", n);			/*�����ַ���*/
		/*���г���У��,�������ַ�������lensʱ,��������*/
		if ((int)strlen(n)>lens)	/*strlen����Ϊsize_t����*/
		{
			printf("\n exceed the required length!	\n");
		}
	} while ((int)strlen(n) > lens);
	
	strcpy(Buffer, n);/*��������ַ������Ƶ��ַ���Buffer��*/
	return;	
}

void Del(PLINK pL)
{
	extern int saveflag;
	int select;
	PNODE p;
	PNODE r;	/*rָ��ɾ�����ǰһ�����*/
	char findmess[20];
	
	if (!pL->pnext)
	{
		system("cls");
		printf("\nû��ѧ����¼\n");
		getchar();
		return;
	}
	
	system("cls");
	
	printf("\n  ====>���1:Delete by number      ======> ���2:delete by name");
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
			printf("\n==========>ɾ���ɹ�!\n");
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
			printf("\n=====>ɾ���ɹ�!\n");
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
	printf("\nû���ҵ���ѧ����Ϣ!\n");
	return;
}

void Disp(PNODE pL)  /*��ʾ������l�д洢��ѧ����¼������Ϊstudent�ṹ�ж��������*/
{
	PNODE p = pL->pnext;
	if (!p)
	{
		printf("\n====>û��ѧ����¼!\n");
		getchar();		
	}
	else
	{
		printf("\n\n");
		PrintHeader();		/*������ͷ��*/

		while(p)
		{
			PrintData(p);
			printf(HEADER3);
			p = p->pnext;
		}
		getchar();
	}
	
	getchar();	/*��ÿ��returnǰҪ����һ��getchar()���,���߻�һ������*/
	return;

	
}

NODE *Locate(PLINK pL, char findmess[], char nameornum[])
{
	PNODE r = NULL;
	/**
	����Ų�ѯ
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
	����������ѯ
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
	int select; /*1:����ѧ�Ų���,2:������������,����,����������(�˵�)*/
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
			printf("�����������");
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
		printf("\nû��ѧ����¼\n");
		getchar();
		return;
	}
	system("cls");
	printf("�޸�ѧ������");
	
	StringInput(findmess,10,"input the existing student number:"); /*���벢�����ѧ��*/
	p=Locate(pL,findmess,"num"); /*��ѯ���ýڵ�*/
	if(p) /*��p!=NULL,�����Ѿ��ҵ��ýڵ�*/
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
		printf("\n�޸ĳɹ�!\n");
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
	PNODE p,v,newinfo; /*pָ�����λ�ã�newinfoָ�²����¼*/
	char ch,num[10],s[10];  /*s[]��������λ��֮ǰ��ѧ��,num[]����������¼�¼��ѧ��*/
	int flag=0;
	v=pL->pnext;
	system("cls");
	Disp(pL);
	while(1)
	{
		StringInput(s,10,"please input insert location  after the Number:");
		flag=0;
		v=pL->pnext;
		while(v) /*��ѯ��ѧ���Ƿ���ڣ�flag=1��ʾ��ѧ�Ŵ���*/
		{
			if(strcmp(v->data.ID, s)==0)  {flag=1;break;}
			v=v->pnext;
		}
		if(flag==1)
		{
			break; /*��ѧ�Ŵ��ڣ�����в���֮ǰ���¼�¼���������*/
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
	/*�����¼�¼�����������Add()��ͬ*/
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
		printf("\n allocate memory failure "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
		return ;             /*����������*/
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
	saveflag=1; /*��main()�жԸ�ȫ�ֱ������жϣ���Ϊ1,����д��̲���*/
	/*��ָ�븳ֵ��p,��Ϊl�е�ͷ�ڵ����һ���ڵ��ʵ�ʱ�����ѧ���ļ�¼*/
	p=pL->pnext;
	while(1)
	{
		if(strcmp(p->data.ID,s)==0) /*�������в���һ���ڵ�*/
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
	
	PNODE pm,pe,pc,pt; /*����ָ�������ߵĽڵ�*/
	PNODE r=pL->pnext;
	int countc=0,countm=0,counte=0; /*�������ųɼ��в����������*/
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
	
	printf("\n------------------------------ͳ�ƽ��--------------------------------\n");
	printf("C���Գɼ�<60:%d (��)\n",countc);
	printf("��ѧ�ɼ�  <60:%d (��)\n",countm);
	printf("Ӣ��ɼ�   <60:%d (��)\n",counte);
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

	ll=(PNODE)malloc(sizeof(NODE)); /*���ڴ����µĽڵ�*/
	if(!ll)
	{
		printf("\n allocate memory failure "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
		return ;             /*����������*/
	}
	ll->pnext=NULL;
	system("cls");
	p=pL->pnext;
	while(p) /*p!=NULL*/
	{
		s=(PNODE)malloc(sizeof(NODE)); /*�½��ڵ����ڱ����ԭ������ȡ���Ľڵ���Ϣ*/
		if(!s) /*s==NULL*/
		{
			printf("\n allocate memory failure "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
			return ;             /*����������*/
		}
		s->data=p->data; /*��������*/
		s->pnext=NULL;    /*ָ����Ϊ��*/
		rr=ll;
		/*rr�����ڴ洢���뵥���ڵ�󱣳����������ll����������ͷָ��,ÿ�δ�ͷ��ʼ���Ҳ���λ��*/

		while(rr->pnext!=NULL && rr->pnext->data.total>=p->data.total)
		{
			rr=rr->pnext;/*ָ�������ֱܷ�p��ָ�Ľڵ���ܷ�С�Ľڵ�λ��*/
		} 
		if(rr->pnext==NULL)/*��������ll�е����нڵ���ܷ�ֵ����p->data.total��ʱ���ͽ�p��ָ�ڵ��������β��*/
		{
			rr->pnext=s;
		}
		else /*���򽫸ýڵ��������һ���ܷ��ֶα���С�Ľڵ��ǰ��*/
		{
			s->pnext=rr->pnext;
			rr->pnext=s;
		}
		p=p->pnext; /*ԭ�����е�ָ������һ���ڵ�*/
	}

	pL->pnext=ll->pnext; /*ll�д洢�ǵ�������������ͷָ��*/
	p=pL->pnext;           /*���ź����ͷָ�븳��p��׼����д����*/
	while(p!=NULL)  /*��p��Ϊ��ʱ���������в���*/
	{
		i++;       /*������*/
		p->data.mingci=i;   /*�����θ�ֵ*/
		p=p->pnext;   /*ָ�����*/

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
	fp=fopen(FILE_PATH,"wb");/*��ֻд��ʽ�򿪶������ļ�*/
	if(fp==NULL) /*���ļ�ʧ��*/
	{
		printf("\n=====>�ļ��򿪴���!\n");
		getchar();
		return ;
	}
	
	p=pL->pnext;

	while(p)
	{
		if(fwrite(p,sizeof(NODE),1,fp)==1)/*ÿ��дһ����¼��һ���ڵ���Ϣ���ļ�*/
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
	fclose(fp); /*�رմ��ļ�*/
}



