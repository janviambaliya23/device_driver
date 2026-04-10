#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	char c;
	int fd =open("/dev/driver0",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		return 0;
	}
	while(read(fd,&c,1))
		putchar(c);
	close(fd);

	

}

