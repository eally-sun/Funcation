/*
 * =====================================================================================
 *
 *       Filename:  sever.c
 *
 *    Description:  读取配置文件的函数
 *
 *        Version:  1.0
 *        Created:  2013年10月09日 16时17分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  eally-chen, eallyclw@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 20


/*这个函数不但可以可以判断。组名，还可以判断你所注释，对于你的注释，是直接可以忽略的*/

typedef  struct Serverini 
{
	char     groupname[size];
	char     ip[size];
	char     hostname[size];
}INI;


int ini_parse (char *buffersize , INI *Temp)
{
	char            *p = buffersize ;
	char            *group_start= NULL ;
	char            *key_start = NULL;
	char            *value_start = NULL ;

	unsigned int    stringlen ;
	
	enum _State 
	{
		STAT_NONE = 0 ,//空白
		STAT_GROUP , //组名
		STAT_KEY  ,   //配置项名称
		STAT_VALUE,  //配置文件名
		STAT_COMMENT  //注释


	}state = STAT_NONE ;


	for (p = buffersize ; *p !='\0' ; p++)
	{
		switch (state)
		{
			case STAT_NONE:
				//解析组名
				if (*p == '[')
				{
					state = STAT_GROUP ;
					group_start = p + 1 ;
				}
				//如果遇到注释
				else if (*p == '#')
				{
					state = STAT_COMMENT;
				}
				//如果遇到非空的字符，且不是上面的三种情况，就按一下的处理
				else if (!isspace (*p))
				{
					state = STAT_KEY ;
					key_start = p ;
				}
				break;
			case STAT_GROUP:
				if (*p == ']')
				{
					*p = '\0';
					state = STAT_NONE ;
					stringlen = strlen (group_start);
					strncpy(Temp->groupname , group_start, stringlen );
			        }
				break;
			case STAT_COMMENT :
				//读取换行符，结束"注释状态。回到空白状态"
				if (*p =='\n')
				{
					state = STAT_NONE ;
					break;
				}
				break;
			case STAT_KEY :
				//在配置项的状态下读取字符'='
				if (*p == '=')
				{
					*p = '\0';
					state = STAT_VALUE ;
                                        value_start = p + 1;
				}
				break;
			case STAT_VALUE:
				if (*p == '\n' || *p== '\r')
				{
					*p = '\0';
					state = STAT_NONE ;
					 
			        }
				break;
			default :
				break;

		}
	}
        
	//如果结构体中的项增加，只需要在这里增加所要判断，就可以完成一个配置文件的解析
	if ( key_start!= NULL && strcmp (key_start , "Ip")==0 )
	{
		
		strcpy(Temp->ip ,value_start) ;

	}
	if (key_start!= NULL && strcmp(key_start , "hostname") ==0 )
	{
		strcpy(Temp->hostname ,value_start) ;
	}
        

	return  0 ;
	

}
int readfile ()
{
	FILE  *fp ;
	char   buffer[size] ;
	INI    temp ;

        memset (buffer, '0',size );
	fp = fopen ("sever.conf", "rt");
	if (fp == NULL)
	{
		fprintf (stderr , "cannot open the file \n");
		return 0 ;
	}
	while ((fgets (buffer, size , fp))!= NULL)
	{
		//printf ("%s", buffer);
		ini_parse (buffer, &temp);
		memset (buffer , '0', size);
	}
	printf ("%s  \n%s \n%s \n", temp.groupname, temp.ip , temp.hostname);


}

int main(int argc, char *argv[])
{
         readfile () ;

	return EXIT_SUCCESS;
}

