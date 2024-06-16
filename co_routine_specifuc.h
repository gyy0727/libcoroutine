/*************************************************************************
	> File Name: co_routine_specifuc.h
	> Author: muqiu0614
	> Mail: 3155833132@qq.com 
	> Created Time: Sat 08 Jun 2024 08:13:17 PM CST
 ************************************************************************/

#include <cstddef>
#include <cstdlib>
#include<iostream>
#include<pthread.h>
#include<stdlib.h>
extern int co_setspecific(pthread_key_t key,const void* value);//*函数定义
extern void* co_getspecific(pthread_key_t key);

#define CO_ROUTINE_SPECIFIC(name ,y)  \
	\
static pthread_once_t _routine_once##name = PTHREAD_ONCE_INIT; \
static pthread_key_t _routine_key_##name;                   \						
static int _routine_init_##name = 0;           \
static void _routine_make_key_##name();    \
{\
	(void) pthread_key_create(&_routine_key_##name,NULL); \
}\
template <class T>\
class clsRoutineData_routine_##name\
{\
pubilc:\
		inline T* operator->()\
		{\
			if(!_routine_init_#name)\
			{\
				pthread_once(&_routine_once##name,_routine_make_key_##name);\
					_routine_init_#name=1;\
\
			}\
			T* p=(T*)co_getspecific(_routine_key_##name,p);\
			if(!p)\
			{\
				p=(T*)calloc(1,sizeof(T));\
				int ret=co_setspecific(_routine_key_##name, p);\
				if(ret){\
					if(p)\
					{\
						free(p);\
							p=NULL;\
					}\
				}\
			}\
			return p;\
\
		}\
\	

static clsRoutineData_routine_##name<name> y;






