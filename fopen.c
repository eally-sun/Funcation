/*
 * =====================================================================================
 *
 *       Filename:  fopen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 20时55分13秒
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>




int funcation  (char *mode)
{
	if (strcmp (mode , "r") == 0)
	{
		return  4 ;
	}else if  (strcmp (mode , "w") == 0)
	{
		return 2 ;
	}else if (strcmp (mode , "w+") == 0 )
	{
		return  6 ;
	}else if (strcmp (mode , "r+") == 0)
	{
		return 6 ;
	}


}
FILE * fopenfile (char *filename , char *mode)
{
	int   fd ;
	int   number ; 
	FILE  *fp ;
        

	number = funcation (mode); //解析权限
	
	if (strcmp (mode , "w+")==0 )
	{
		fd = creat(filename , S_IRUSR|S_IWUSR);
	}
         
	fd = open (filename, number  );
	
	if (fd == -1)
	{
		fprintf (stderr ,"it has not the filename\n");
		return NULL ;

	}
	fp = fdopen (fd, mode);
	if (fp == NULL)
	{
		fprintf (stderr , "操作失败\n");
		return NULL  ;
	}
	return fp ;

}


int fclose (FILE *fp)
{
	int fd = fileno (fp);
	printf ("关闭文件\n");
	close (fd);
	return 0 ;
}

int main(int argc, char *argv[])
{
	FILE  *fp ;
	FILE  *fhead ;
	char   temp[20];
	memset (temp , '\0', 20);
/*	fhead = fopen ("wr", "w+");
	if (fhead == NULL)
	{
		printf ("error\n");
		return -1 ;
	}*/
	fp = fopenfile ("hello.txt", "w+");
	if (fp == NULL)
	{
		fprintf (stderr , "cannot open the file\n");
		return -1;
	}
	while ((fgets (temp , 20 , fp))!= NULL)
	{
		printf ("%s", temp);
		memset (temp , '\0', 20);
	}
	fclose (fp);
	
	
	 


	return EXIT_SUCCESS;
}

