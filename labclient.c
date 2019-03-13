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
    to.sin_port = htons(atoi(argv[2]));
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
    
    int seqno = 0;
    char send[100];
    char rcv[100];
    int src_addr_size;
    int rcvack;
    
    while(1)
	{	
		for(int i=0;i<100;i++)
		{
			send[i] = '\0';
		}
		
		printf("Enter Seqno of Data to be sent\n");
        scanf("%d",&seqno);
        printf("Enter Data to be sent\n");
        scanf("%s",send);

        sendto(socketfd, seqno , strlen(seqno) , 0, (const struct sockaddr *)&to, sizeof(to));
        sendto(socketfd, send , strlen(send), 0, (const struct sockaddr *)&to, sizeof(to));
        
    
		recvfrom(socketfd, rcvack, 1 , 0, (struct sockaddr *)&to, &src_addr_size);
		printf("%d",rcvack);
		
  		if(rcvack == seqno+1)
  		{
  		        printf("Data Trainsmitted Succesfully");
  		}
  		else if(rcvack == -1)
  		{
  		        printf("ReTrainsmit Data with sequence no %d",seqno);
  		}
  		if(strcmp(send,"Bye")==0)
		{
		    printf("Connection Terminated\n");
		    break;
    	}
  		
	}
    return 0;
}
