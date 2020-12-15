
#include<stdio.h>
#include "ctx.h"
void func1 (void)
{
        printf("func1 start\n");
	coroutine_yield();
	printf("func1 exit\n");

}

void func2 (void)
{
        printf("func2 start\n");
	coroutine_yield();
        printf("func2 exit\n");


}

int main (void)
{
	int co_id1;
	int co_id2;
	
	co_id1=coroutine_create(func1);
	co_id2=coroutine_create(func2);
	coroutine_resume(co_id1);
	coroutine_resume(co_id2);
        printf("main exit\n");
        return 0;

}
