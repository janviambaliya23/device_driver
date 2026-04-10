#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int c;
	char ch[30];
	while(1)
	{
		printf("Enter the string according to option..\n1) write string\n2)read string\n3)exit\n");
		scanf(" %d",&c);
		switch(c)
		{
			case 1: printf("Enter the string...\n");
				scanf(" %[^\n]",ch);
				int fd=open("/dev/vvdn_driver",O_WRONLY);
				write(fd,ch,strlen(ch)+1);
				close(fd);
				break;
			case 2:int fd1=open("/dev/vvdn_driver",O_RDONLY);
			       read(fd1,ch,sizeof(ch));
			     printf("string is-> %s\n",ch);
				   close(fd1);
			       break;
			case 3:exit(0); 
				break;
			defualt:printf("unknown option..\n"); 
				break;
		}

	
	}


}
