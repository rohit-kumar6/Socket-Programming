#include <stdio.h>
#include <stdlib.h>

struct number{
	int x;
	int y[2];
	int z;
	}n;

int main(int argc,char* argv[])
{
	int no = atoi(argv[1]);
	char* ptr = (char*) &no;
	n.x = *ptr;
	n.y[0] = *(++ptr);
	n.y[1] = *(++ptr);
	n.z = *(++ptr);
	
	// printf("%d %d %d %d",n.x,n.y[0],n.y[1],n.z);
	int b = n.z;
	b = b<<8;
	b = b|n.y[1];
	b = b<<8;
	b = b|n.y[0];
	b = b<<8;
	b = b|n.x;
	printf("%d\n",b);
	
	return 0;
}
