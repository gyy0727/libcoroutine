/*************************************************************************
	> File Name: coctx.cc
	> Author: muqiu0614
	> Mail: 3155833132@qq.com
	> Created Time: Sat 08 Jun 2024 08:47:42 PM CST
 ************************************************************************/

#include "coctx.h"
#include <iostream>
#include <string.h>

//*寄存器在regs数组对应的位置
/*
#define ESP 0
#define EIP 1
#define EAX 2
#define ECX 3
// -----------
#define RSP 0
#define RIP 1
#define RBX 2
#define RDI 3
#define RSI 4

#define RBP 5
#define R12 6
#define R13 7
#define R14 8
#define R15 9
#define RDX 10
#define RCX 11
#define R8 12
#define R9 13
*/
#define ESP 0 // ESP: Extended Stack Pointer，指向当前栈顶
#define EIP 1 // EIP: Extended Instruction Pointer，指向下一条要执行的指令
#define EAX 2 // EAX: Extended Accumulator Register，主要用于存放运算结果
#define ECX 3 // ECX: Extended Count Register，主要用于循环计数
// -----------
#define RSP 0 // RSP: Stack Pointer，指向当前栈顶
#define RIP 1 // RIP: Instruction Pointer，指向下一条要执行的指令
#define RBX 2 // RBX: Base Register，用于数据存取
#define RDI 3 // RDI: Destination Index，用于字符串和数组操作的目的地址
#define RSI 4 // RSI: Source Index，用于字符串和数组操作的源地址
#define RBP 5  // RBP: Base Pointer，指向当前栈帧的基地址
#define R12 6  // R12: General Purpose Register，通用寄存器
#define R13 7  // R13: General Purpose Register，通用寄存器
#define R14 8  // R14: General Purpose Register，通用寄存器
#define R15 9  // R15: General Purpose Register，通用寄存器
#define RDX 10 // RDX: Data Register，用于存放数据和I/O端口地址
#define RCX 11 // RCX: Count Register，用于循环计数
#define R8 12  // R8: General Purpose Register，通用寄存器
#define R9 13  // R9: General Purpose Register，通用寄存器
/*
 * 缺少
 * #define RDX 10 // RDX: Data Register，用于存放数据和I/O端口地址
 * #define RCX 11 // RCX: Count Register，用于循环计数
*/

enum {
	kEIP = 0,
	kESP = 7
};
enum {
	kRDI = 7,
	kRSI = 8,
	kRETAddr = 9,
	kRSP = 13
};

extern "C" {
extern void coctx_swap(coctx_t*, coctx_t*) asm("coctx_swap");
}

#if defined(__i386__)
//*初始化协程的上下文
int coctx_init(coctx_t* ctx)
{
	memset(ctx, 0, sizeof(*ctx));
	return 0;
}
int coctx_make(coctx_t* ctx, coctx_pfn_t pfn, const void* s, const void* s1)
{
	char* sp = ctx->ss_sp + ctx->ss_size - sizeof(coctx_param_t); // *sp就是目前的栈顶,给coctx_param_预留空间
	sp = (char*)((unsigned long)sp & -16L);						  //*内存对齐,为什么对齐16个字节,很重要???转成(char*)是因为是一个字节,方便对齐
	coctx_param_t* param = (coctx_param_t*)sp;
	param->s1 = s;
	param->s2 = s1;
	memset(ctx->regs, 0, sizeof(ctx->regs));
	ctx->regs[kESP] = (char*)sp - sizeof(void*); //函数调用，压入参数之后，还有一个返回地址要压入，所以还需要将sp往下移动4个字节，32位汇编获取参数是通过EBP+4, EBP+8来分别获取第一个参数，第二个参数的，这里减去4个字节是为了对齐这种约定,这里可以看到对齐以及参数还有4个字节的虚拟返回地址已经占用了一定的栈空间，所以实际上供协程使用的栈空间是小于分配的空间。另外协程且走调用co_swap参数入栈也会占用空间，
	ctx->regs[kEIP] = (char*)pfn;				 // regs[0]填入函数地址，即新协程要执行的指令地址
}
#elif defined(__x86_64__)
int coctx_make(coctx_t* ctx, coctx_pfn_t pfn, const void* s, const void* s1)
{
	char* sp = ctx->ss_sp + ctx->ss_size; //*64位系统有十六个寄存器,无需结构体来存储数据
	sp = (char*)((unsigned long)sp & -16LL);
	memset(ctx->regs, 0, sizeof(ctx->regs));
	ctx->regs[kRSP] = sp - 8;
	ctx->regs[kRETAddr] = (char*)pfn; //*like ret(asm)
	ctx->regs[kRDI] = (char*)s;
	ctx->regs[kRSI] = (char*)s1;
	return 0;
}
int coctx_init(coctx_t* ctx)
{
	memset(ctx, 0, sizeof(*ctx));
	return 0;
}

#endif
//
