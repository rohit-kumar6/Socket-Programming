#include <stdio.h>
#include <stdlib.h>

struct student 
{
        char name[20];
        int roll;
};

void display(struct student stu)
{
        printf("%s\n",stu.name);
        printf("%d\n",stu.roll);
}
int main()
        {
                struct student st;
                scanf("%s",st.name);
                scanf("%d",&st.roll);
                
                display(st);
             
                
                return 0;
        }
        
