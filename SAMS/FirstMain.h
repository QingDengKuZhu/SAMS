/*************************************
**包含一些头文件文件
**************************************/

#ifndef FIRSTMAIN_H
#define FIRSTMAIN_H

#define FILE_PATH	"DATABASE"	/*指定数据库文件名,若未指定路径,则在当前工作目录*/

#define HEADER1		"      ----------------------------STUDENT----------------------------------  \n"	
#define HEADER2		"     |    number     |      name     |Comp|Math|Eng |   sum  |  ave  |mici | \n"
#define HEADER3		"     |---------------|---------------|----|----|----|--------|-------|-----| "

#define FORMAT		"        |    %-10s |%-15s|%4d|%4d|%4d| %4d   | %.2f |%4d |\n"
#define DATA		p->data.ID,p->data.name,p->data.egrade,p->data.mgrade,p->data.cgrade,p->data.total,p->data.ave,p->data.mingci /*不能用空格分隔*/

#define END			"       --------------------------------------------------------------------- \n"






#endif