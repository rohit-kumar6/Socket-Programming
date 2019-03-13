#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
        {
                int no=atoi(argv[1]);
               
                unsigned char* ptr = (char*)&no;
                int firstbyte = *ptr;
                
                for(int i=0;i<4;i++)
                {
                      printf("%d byte %d\n",i+1,*ptr);
		      ptr++;
                }
                int lastbyte  = *ptr;
              
		
                if(firstbyte == lastbyte)
                {
                printf("Wrong Input Run again with deifferent input\n");
		//because if firstbyte == lastbyte we cant predict is my computer support big endian or little endian
                return 0;
                }
              
              
                //printf("%d %d\n",firstbyte,lastbyte);
                
                int bitand;
                
                bitand = no & 0x000000ff;
                
                printf("After Bitwise and operation -> %d\n",bitand);
                
                if(firstbyte == bitand)
                printf("Little Endian\n");
		else
		printf("Big Endian\n");
             
                return 0;
        }
        
