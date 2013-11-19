/*************************************
**ϵͳ������
**************************************/

#include "Data.h"
#include "DataFucntion.h"
#include "FirstMain.h"
#include <stdio.h>
#include <stdlib.h>

int saveflag = 0;		/* ���̱�־,����������,ɾ,�Ĳ���,��saveflag��Ϊ1 */

int main(void)
{
	PLINK pL = NULL;		/*������ͷָ��*/	
	FILE *pf = NULL;		/*�ļ�ָ��*/
	int select;				/*�����û�ѡ����*/
	char ch;				/*����(y,Y,n, N)*/
	int count = 0;			/*�����ļ��е�ѧ����Ϣ����*/
	PNODE p	= NULL;			/*���ָ��*/
	PNODE r = NULL;			/*ָ��β���,������Ϊ��,�����ͷָ��*/

	
	/*
	**��ʼ��������,����ͷ���.
	*/
	pL = (PNODE)malloc(sizeof(NODE));
	if (!pL)
	{
		printf("ͷ������ʧ��!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pL->pnext = NULL;
		r = pL;
	}

	/*
	**��׷�ӵķ�ʽ��һ���������ļ�
	**�ɶȿ�д,���ļ�������,�򴴽���
	**��.
	*/
	pf = fopen(FILE_PATH, "ab+");
	if (!pf)
	{
		printf("�ļ��򿪴���");
		exit(EXIT_FAILURE);
	}
	

	/*
	**��������
	*/
	while (0 == feof(pf))	/*���ļ�δ����β��*/
	{
		p = (PNODE)malloc(sizeof(NODE));
		if (!p)
		{
			printf("���������ݽ������ʧ��!\n");
			exit(EXIT_FAILURE);
		}
		
		/*
		**һ�δ��ļ��ж�ȡһ��ѧ����¼
		*/
		if ( 1 == fread(p, sizeof(NODE), 1, pf) )
		{
			p->pnext = NULL;
			r->pnext = p;
			r = p;
			++count;	/*�ļ���¼��һ*/
		}

	}

	fclose(pf);/*�ر��ļ�*/

	printf("�ļ��ɹ���,��ǰ��¼��%d��\n", count);
	getchar();		/*����������Ϣһ������*/
	

	while (1)	/* while_@ */
	{
		system("cls");	/*����*/
		Menu();			/*��ʾ�˵�,���û�ѡ��*/

		p = r;
		printf("\n				���������ѡ��(0~9)			\n");
		scanf("%d", &select);

		if ( 0 == select)
		{
			/**
			����������������޸���δ���д��̲���,���־saveflagΪ1.
			**/
			if (1 == saveflag)
			{
				getchar();//����س�
				printf("�Ƿ񱣴�����(Y|N)?");
				scanf("%c", &ch);
				if (ch=='Y'||ch=='y')
				{
					Save(pL);
				}
			}
			printf("ллʹ��!\n");
			getchar();
			break;/*����while_@ѭ��*/
		}
		else
		{
			switch (select)
			{
			case 1:					/*����ѧ����¼*/
				Add(pL);			
				break;
			case 2:					/*ɾ��ѧ����¼*/
				Del(pL);
				break;
			case 3:					/*��ѯѧ����¼*/
				Qur(pL);
				break;
			case 4:					/*�޸�ѧ����¼*/
				Modify(pL);
				break;
			case 5:					/*����ѧ����¼*/
				Insert(pL);
				break;
			case 6:					/*ͳ��ѧ����¼*/
				Tongji(pL);
				break;
			case 7:					/*��ѧ����¼����*/
				Sort(pL);
				break;
			case 8:					/*����ѧ����¼*/
				Save(pL);
				break;
			case 9:					/*��ʾѧ����¼*/
				system("cls");
				Disp(pL);
				break;
			default:				/*����ֵ����ʱ����취*/
				Wrong();
				getchar();
				break;/* ����while_@ѭ�� */
			}
		}
	}/* while_@ */


	return EXIT_SUCCESS;
}