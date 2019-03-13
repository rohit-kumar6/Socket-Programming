#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>


int main()
{
	int fd = 0;
    	struct timeval time;
	time.tv_sec =2;
	//int cfd = 0;
	fd_set readfd;
	FD_ZERO(&readfd);
	FD_SET(fd,&readfd);
	int nfds = fd + 1;
	char buf[100];


	int res=select(nfds,&readfd,NULL,NULL,&time);
	if(res==0)
		printf("not pressed");
	if(res==-1)
		printf("Select error");
	if(FD_ISSET(fd,&readfd)){
		read(fd,buf,100);
		printf("Pressed %s ",buf);}		
	return 0;
}
