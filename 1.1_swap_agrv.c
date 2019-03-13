#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
        {
                int a,b;
                a = atoi(argv[1]);
                b = atoi(argv[2]);
                int temp = a;
                a = b;
                b = temp;
                
                printf("a: %d\n",a);
                printf("b: %d\n",b);
                
                return 0;
        }
        
