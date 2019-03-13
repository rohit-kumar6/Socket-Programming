#include <stdio.h>
#include <stdlib.h>  
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char** argv)
{
	int sockfd;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
		printf("SOCKET ERROR");
	
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	
	int con=connect(sockfd,(const struct sockaddr*)&server,sizeof(server));
	if(con==-1)
		printf("CONNECT ERROR");
		
	
	char *arr = (char *) malloc(100 * sizeof(char)); 
	char *buf =  (char *) malloc(100 * sizeof(char));
	while(1)
	{
		for(int i=0;i<100;i++)
		{
			arr[i] = '\0';
			buf[i] = '\0';
		}	
		int recvsize = recv(sockfd,buf,100,0);
		printf("%s",buf);
		
		if(recvsize<100)
			break;
		
	}
	
	char filename[100];
	printf("Enter File to Download\n");
	scanf("%s",filename);	
	send(sockfd,filename,strlen(filename),0);

	FILE *fp;
	fp=fopen(filename,"w");

	while(1)
	{
		for(int i=0;i<100;i++)
		{
			arr[i] = '\0';
			buf[i] = '\0';
		}	
		int recvsize = recv(sockfd,buf,100,0);
		printf("%s",buf);
		fwrite(buf,1,100,fp);
		
		if(recvsize<100)
			break;
		
	}
	fclose(fp);


	close(sockfd);
	return 0;
}
