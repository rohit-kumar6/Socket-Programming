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


int main(int argc,char* argv[])
{
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(argv[1]));
    myaddr.sin_addr.s_addr = INADDR_ANY;
    
    
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

	int maxfd = socketfd + 1;
	int acceptsockfd[100];
	
	int i = 0;
	char buf[100];
	char rcv[100];
	
	fd_set readfd;
	FD_ZERO(&readfd);
	FD_SET(socketfd,&readfd);


	while(1)
	{
		
		select(maxfd,&readfd,NULL,NULL,NULL);
		if(FD_ISSET(socketfd,&readfd))
		{
			struct sockaddr_in theiraddr;			
			int src_size;
			acceptsockfd[i] = accept(socketfd, (struct sockaddr *)&theiraddr, &src_size);
			
			if(acceptsockfd[i] == -1)
				perror("Accept Error");
			
			FD_SET(acceptsockfd[i],&readfd);

			if(acceptsockfd[i] > maxfd)
				maxfd = acceptsockfd[i] + 1;
			
			i++;
			
		}
		int j=0;
		for(j=0;j<i;j++)
		{
			if(FD_ISSET(acceptsockfd[j], &readfd))
			{
				
				while(1)
				{
					recv(acceptsockfd[j], rcv, sizeof(rcv) , 0);
		    			printf("%s",rcv);
		    			if(strcmp(rcv,"Ended")==0)
		    			{
						printf("\nUser Left\n");
						break;
				    	}
				    	fgets(buf,255,stdin);
				    	send(acceptsockfd[j], buf , strlen(buf), 0);
				    	if(strcmp(buf,"Ended")==0)	
				    	{   
						printf("\nConnection Terminated\n");
						break;
				    	}
				}
			}
		}
            	
	}
	close(socketfd);
	return 0;
}
