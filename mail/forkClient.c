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
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port= htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    
    int socketfd = socket(AF_INET , SOCK_STREAM , 0);
    if (socketfd == -1)
    {
        perror("Socket Error");
    }
    else
    {
        printf("Socket Connected\n");
    }
    
    int con = connect(socketfd, (const struct sockaddr *)&server, sizeof(server));
    if (con == -1)
    {
        perror("Connection Error");
    }
    else
    {
        printf("Connection Establish\n");
    }

    char buf[100];
    char rcv[100];
    
    while(1)
	{
		scanf("%s",buf);
            	send(socketfd, buf , strlen(buf), 0);
            	if(strcmp(buf,"Ended")==0)
            	{
                	printf("\nConnection Terminated\n");
                	break;
            	}
            	recv(socketfd, rcv, sizeof(rcv) , 0);
            	printf("%s\n",rcv);
            	if(strcmp(rcv,"Ended")==0)
            	{
                	printf("\nUser Left\n");
                	break;
            	}
    	}
   close(socketfd);
   return 0;
}
