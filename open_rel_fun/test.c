#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("usage ./a.out arg");
		return 0;
	}
	int fd =open(argv[1],O_RDONLY);
	if(fd<0)
	{
		perror("open");
		return 0;
	}
	close(fd);

	 fd =open(argv[1],O_RDWR|O_SYNC);
	if(fd<0)
	{
		perror("open");
		return 0;
	}
	close(fd);
 	
	fd =open(argv[1],O_WRONLY|O_NONBLOCK);
	if(fd<0)
	{
		perror("open");
		return 0;
	}
	close(fd);

}
