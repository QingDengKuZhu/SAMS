/*************************************
**����һЩͷ�ļ��ļ�
**************************************/

#ifndef FIRSTMAIN_H
#define FIRSTMAIN_H

#define FILE_PATH	"DATABASE"	/*ָ�����ݿ��ļ���,��δָ��·��,���ڵ�ǰ����Ŀ¼*/

#define HEADER1		"      ----------------------------STUDENT----------------------------------  \n"	
#define HEADER2		"     |    number     |      name     |Comp|Math|Eng |   sum  |  ave  |mici | \n"
#define HEADER3		"     |---------------|---------------|----|----|----|--------|-------|-----| "

#define FORMAT		"        |    %-10s |%-15s|%4d|%4d|%4d| %4d   | %.2f |%4d |\n"
#define DATA		p->data.ID,p->data.name,p->data.egrade,p->data.mgrade,p->data.cgrade,p->data.total,p->data.ave,p->data.mingci /*�����ÿո�ָ�*/

#define END			"       --------------------------------------------------------------------- \n"






#endif