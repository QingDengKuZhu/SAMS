/*************************************
**与系统有关的函数声明
**************************************/

#ifndef DATAFUNTION_H
#define DATAFUNTION_H

#include "Data.h"
#include "FirstMain.h"

/*
**格式化输出表头,当以表格形式输出用户信息是输出表头信息.
*/
void PrintHeader(void);

/*
**格式化输出表中一条数据(一个学生的信息),打印输出指针p所
**指向的学生信息.
*/
void PrintData(PNODE p);

/*
**根据提示信息,输入分数,并对输入的分数进行合理性验证,若
**满足条件,则返回输入的分数,notice[]保存提示信息.
*/
unsigned int NumberInput(char notice[]);


/*
**格式化输出所有学生信息.
*/
void Disp(PLINK pL);

/*
**定位链表中满足要求的结点,并返回指向该节点的指针
**findmess[]保存要查找的具体内容,char nameorID[]保
**存按照什么查找(名字或ID).
*/
PNODE Locate(PLINK pL, char findmess[], char nameorID[]);

/*
**向系统中增加新的用户记录.
*/
void Add(PLINK pL);

/*
**按照ID或姓名来查找用户记录.
*/
void Qur(PLINK pL);

/*
**删除系统中的特定用户记录.
*/
void Del(PLINK pL);

/*
**修改用户记录,先按照输入的ID查询到该记录,然后提示
**用户修改除ID外的值,ID不能修改.
*/
void Modify(PLINK PL);

/*
**插入记录,按照ID查询到要插入的结点的位置,然后在ID
**之后插入一个新结点.
*/
void Insert(PLINK pL);

/*
**统计各班总分的第一名和单科第一名以及各科不及格人数.
*/
void Tongji(PLINK PL);


/*
**按照总分由高到低排列.
*/
void Sort(PLINK pL);


/*
**对数据进行存盘处理,如果用户没有专门进行此操作
**而对数据有所修改,则在退出系统时会提示用户进行存盘.
*/
void Save(PLINK pL);

/*
**输出错误信息.
*/
void Wrong(void);


/*
**系统主菜单函数,显示系统的主菜单界面,提示用户
**进行相应的选择并完成对应的任务.
*/
void Menu(void);


#endif