#include <stdio.h>
#include <stdlib.h>

void swap(int * a , int * b)
        {
                int temp;
                temp = *a;
                *a = *b;
                *b = temp;
                
                printf("a: %d\n",*a);
                printf("b: %d\n",*b);
                
                return;
        }

int main()
        {
                int a,b;
                scanf("%d %d",&a,&b);
                swap(&a,&b);
                return 0;
        }
        
