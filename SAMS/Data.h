/*************************************
**ϵͳ��������ݽṹ
**************************************/

#ifndef DATA_H
#define DATA_H

/*
**ѧ�����ݽṹ
*/
typedef struct student 
{
	char ID[10];				/**ѧ��**/
	char name[15];				/*����*/

	unsigned int cgrade;		/*C���Գɼ�*/
	unsigned int egrade;		/*Ӣ��ɼ�*/
	unsigned int mgrade;		/*��ѧ�ɼ�*/
	
	unsigned int total;			/*�ܷ�*/
	double ave;					/*ƽ���ɼ�*/
	
	unsigned int mingci;		/*����*/

}STUDENT;


#endif