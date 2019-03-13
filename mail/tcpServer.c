#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc,char* argv[])
{
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(argv[1]));
    myaddr.sin_addr.s_addr = INADDR_ANY;
    
    struct sockaddr_in theiraddr;
    
    int socketfd = socket(AF_INET , SOCK_STREAM , 0);
    if (socketfd == -1)
    {
        perror("Socket Error");
    }
    else
    {
        printf("Socket Connected\n");
    }
    
    int bindfd = bind(socketfd, (const struct sockaddr *)&myaddr,sizeof(myaddr));
    if (bindfd == -1)
    {
        perror("Bind Error");
    }
    else
    {
        printf("Bind Done\n");
    }

    int lis = listen(socketfd,1);
    if (lis == -1)
    {
        perror("Listen Error");
    }
    else
    {
        printf("Listen Done\n");
    }

    int src_size;
    int acceptsockfd = accept(socketfd, (struct sockaddr *)&theiraddr, &src_size);


    printf("Port Used By Sender %d\n",ntohs(theiraddr.sin_port));
    printf("Ip Used By Sender %s\n",inet_ntoa(theiraddr.sin_addr));
    
    char buf[100];
    char rcv[100];
    
    while(1)
	{
            	recv(acceptsockfd, rcv, sizeof(rcv) , 0);
            	printf("%s\n",rcv);
            	if(strcmp(rcv,"Ended")==0)
            	{
                	printf("\nUser Left\n");
                	break;
            	}
            	scanf("%s",buf);
            	send(acceptsockfd, buf , strlen(buf), 0);
            	if(strcmp(buf,"Ended")==0)
            	{   
                	printf("\nConnection Terminated\n");
                	break;
            	}
	}
	close(socketfd);
	close(acceptsockfd);
	return 0;
}
