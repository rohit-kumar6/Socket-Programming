#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
int main(int argc,char* argv[])
{
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(argv[1]));
    myaddr.sin_addr.s_addr = INADDR_ANY;
    
    struct sockaddr_in to;
    to.sin_family = AF_INET;
    to.sin_port= htons(atoi(argv[2]));
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

    int ack = 0;
    int dataseqno = 0;
    //char dataseqno[100];;
    char rcv[100];
    int src_addr_size;
    
    while(1)
	{
		for(int i=0;i<100;i++)
		{
			rcv[i] = '\0';
		}
		
		recvfrom(socketfd, dataseqno, 1 , 0, (struct sockaddr *)&to, &src_addr_size);
		recvfrom(socketfd, rcv, sizeof(rcv) , 0, (struct sockaddr *)&to, &src_addr_size);
	  	printf("Received Sequence no %d \t Data %s",dataseqno,rcv);

	  	if(dataseqno == ack)
	  	{
	  	        ack++;
	  	        sendto(socketfd, ack , 1, 0, (const struct sockaddr *)&to, sizeof(to));
	  	}
        else
	  	{
	  	        sendto(socketfd, -1 , 1, 0, (const struct sockaddr *)&to, sizeof(to));
	  	}

	 	
	}
    return 0;
}
