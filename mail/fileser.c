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
	
	struct sockaddr_in server, client;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	
	
	int sockfd;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
		printf("SOCKET ERROR");

	int bin=bind(sockfd,(const struct sockaddr*)&server,sizeof(server));
	if(bin==-1)
		printf("bind error");
		
	int lis=listen(sockfd,1);
	if(lis==-1)
		printf("LISTEN ERROR");
	
	int temp;
	int acc=accept(sockfd,(struct sockaddr*)&client,&temp);
	if(acc==-1)
		printf("ACCEPT ERROR");


	char arr[100];
	char buf[100];
	system("ls>abc.txt");
	FILE *fp;
	fp=fopen("abc.txt","r");
	
	while(1)
	{
		fread(arr,1,100,fp);
	    	printf("%s",arr);	
		int sendsize = send(acc,arr,strlen(arr),0);
		
		for(int i=0;i<100;i++)
		{
			arr[i] = '\0';
			buf[i] = '\0';
		}
		
		if(sendsize<100)
			break;
	}
	fclose(fp);
	printf("list of file Send Succesfully\n");
	char filetodownload[100];
	
	recv(acc,filetodownload,100,0);
	printf("%s",filetodownload);
	
	fp=fopen(filetodownload,"r");	

	while(1)
	{
	    	fread(arr,1,100,fp);
	    	
		int sendsize = send(acc,arr,100,0);
		
		for(int i=0;i<100;i++)
		{
			arr[i] = '\0';
			buf[i] = '\0';
		}
		
		if(sendsize<100)
			break;
	}
	
	
	close(sockfd);
	return 0;
}
