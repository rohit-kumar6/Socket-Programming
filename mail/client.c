#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
int main()
{
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(6001);
    myaddr.sin_addr.s_addr = INADDR_ANY;
    
    struct sockaddr_in to;
    to.sin_family = AF_INET;
    to.sin_port = htons(6000);
    to.sin_addr.s_addr = INADDR_ANY;
    
    int socketfd = socket(AF_INET , SOCK_DGRAM , 0);
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

    char send[100];
    char rcv[100];
    int src_addr_size;
    
    while(1)
	{	
		for(int i=0;i<100;i++)
		{
			send[i] = '\0';
			rcv[i] = '\0';
		}

		recvfrom(socketfd, rcv, sizeof(rcv) , 0, (struct sockaddr *)&to, &src_addr_size);
  		printf("%s",rcv);

		fgets(send,100,stdin);
          	sendto(socketfd, send , strlen(send), 0, (const struct sockaddr *)&to, sizeof(to));

	}
    return 0;
}
