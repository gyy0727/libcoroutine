/*************************************************************************
	> File Name: co_routine.h
	> Author: muqiu0614
	> Mail: 3155833132@qq.com
	> Created Time: Sun 09 Jun 2024 09:31:21 PM CST
 ************************************************************************/
#ifndef __CO_ROUTINE_H__
#define __CO_ROUTINE_H__
#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/poll.h>

struct stCoRoutine_t;  //*协程结构体
struct stShareStack_t; //*共享栈

struct stCoRoutineAttr_t {
	int stack_size;
	stShareStack_t* share_stack;
	stCoRoutineAttr_t()
	{
		stack_size = 128 * 1024;
		share_stack = NULL;
	}
} __attribute__((packed)); //*紧凑方式内存对齐

struct stCoEpoll_t;
typedef int (*pfn_co_eventloop_t)(void*);
typedef void* (*pfn_co_routine_t)(void*); //*协程函数指针

int co_create(stCoRoutine_t** co, const stCoRoutineAttr_t* attr, void* (*routine)(void*), void* arg); //*Corountine  Created
void co_resume(stCoRoutine_t* co);																	  //*Corountine back to exec
void co_yield (stCoRoutine_t* co);																	  //*让出执行权
void co_yield_ct();																					  //*ct==current
void co_release(stCoRoutine_t* co);
stCoRoutine_t* co_self();
int co_poll(stCoRoutine_t* ctx, struct pollfd fds[], nfds_t nfds, int timeout_ms);
void* co_eventloolp(stCoRoutine_t* ctx, pfn_co_eventloop_t pfn, void* arg);
int co_setspecific(pthread_key_t key, const void* value);
stCoEpoll_t* co_get_epoll_ct(); //*ct==current thread
void co_enable_hook_sys();
void co_disable_hook_sys();
bool co_is_enbale_sys_hook();

struct stCoCond_t;
stCoCond_t* co_cond_alloc();
int co_cond_free(stCoCond_t* cc);

int co_cond_signal(stCoCond_t*);
int co_cond_broadcast(stCoCond_t*);
int co_cond_timewait(stCoCond_t* ,int timeout_ms);

stShareStack_t* co_alloc_sharestack(int iCount, int iStackSize);

void co_set_env_list(const char* name[], size_t cnt);
void co_log_err(const char* fmt, ...);

#endif
