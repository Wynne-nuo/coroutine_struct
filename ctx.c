#include <unistd.h>
#include <ucontext.h>
#define STACK_SIZE (1024 *64)
struct coroutine {
	void (*func)(void);
	char stack[STACK_SIZE];
	ucontext_t ctx;
};

ucontext_t ctx_main;
struct coroutine coroutine_slot[8];
int id_num=0;
int current_id = 0;
int coroutine_create(void (*fn) (void)){

	struct coroutine *rt = &coroutine_slot[id_num];
	rt->func = fn;
	current_id=id_num;
	getcontext (&(rt->ctx));
	rt->ctx.uc_stack.ss_sp  =rt->stack;
	rt->ctx.uc_stack.ss_size =STACK_SIZE;
	rt->ctx.uc_stack.ss_flags =0;
	rt->ctx.uc_link    =&ctx_main;
	
       // ctx_func.uc_link    =NULL;
        makecontext (&(rt->ctx),fn,0);
	swapcontext(&ctx_main,&(rt->ctx));

	return id_num++;


}

int coroutine_yield(void){
	struct coroutine *t = &coroutine_slot[current_id];
	swapcontext (&(t->ctx), &ctx_main);
}


int coroutine_resume(int co_id){
	struct coroutine *t = &coroutine_slot[co_id];
	current_id = co_id;
	swapcontext (&ctx_main,&(t->ctx));

}

	
