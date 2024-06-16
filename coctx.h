/*************************************************************************
	> File Name: coctx.h
	> Author: muqiu0614
	> Mail: 3155833132@qq.com 
	> Created Time: Sat 08 Jun 2024 08:46:42 PM CST
 ************************************************************************/

#ifndef __CO_CTX_H__
#define __CO_CTX_H__
#include<iostream>
#include <stdlib.h>
typedef void* (*coctx_pfn_t)( void* s, void* s2 );

//*对应剩下的两个寄存器(64位regs数组只保存了14个寄存器的值,剩下两个通用数据寄存器),只在64位下使用
struct coctx_param_t
{
	const void *s1;
	const void *s2;
};


//*保存的寄存器值,程序上下文可以理解为就是寄存器的值,栈帧和指令寄存器
struct coctx_t
{
#if defined(__i386__)
	void *regs[ 8 ];
#else
	void *regs[ 14 ];
#endif
	size_t ss_size;//*给协程分配的栈大小
	char *ss_sp;//*协程栈指针
	
};

int coctx_init( coctx_t *ctx );//*将coctx_t结构体内存全部初始化为0
int coctx_make( coctx_t *ctx,coctx_pfn_t pfn,const void *s,const void *s1 );//*类似于makecontext,绑定函数指针给上下文
#endif

