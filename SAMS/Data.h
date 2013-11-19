/*************************************
**系统所需的数据结构
**************************************/

#ifndef DATA_H
#define DATA_H

/*
**学生数据结构
*/
typedef struct student 
{
	char ID[10];				/**学号**/
	char name[15];				/*姓名*/

	unsigned int cgrade;		/*C语言成绩*/
	unsigned int egrade;		/*英语成绩*/
	unsigned int mgrade;		/*数学成绩*/
	
	unsigned int total;			/*总分*/
	double ave;					/*平均成绩*/
	
	unsigned int mingci;		/*名次*/

}STUDENT;


#endif