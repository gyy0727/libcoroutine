/*************************************************************************
        > File Name: co_epoll.h
        > Author: muqiu0614
        > Mail: 3155833132@qq.com
        > Created Time: Mon 10 Jun 2024 11:10:56 AM CST
 ************************************************************************/
#ifndef __CO_EPOLL_H__
#define __CO_EPOLL_H__

#include <assert.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>

#include <sys/types.h>
#include <time.h>

#if !defined(__APPLE__) && !defined(__FreeBSD__)

struct co_epoll_res {
  int size;
  struct epoll_event *events;
  struct kevents *eventlist;
};

int co_epoll_wait(int epfd, struct co_epoll_res *events, int maxevents,
                  int timeout);
int co_epoll_ctl(int epfd, int op,int fd, struct epoll_event *);
int co_epoll_create(int size);
struct co_epoll_res *co_epoll_res_alloc(int n);
void co_epoll_res_free(struct co_epoll_res *);

#else
enum EPOLL_EVENTS {
  EPOLLIN = 0x001,
  EPOLLRI = 0x002,
  EPOLLOUT = 0x004,
  EPOLLERR = 0x008,
  EPOLLHUP = 0x010,
  EPOLLRDNORM = 0x40,
  EPOLLWRNORM = 0x004

};
#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3

typedef union epoll_data {
  void *ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
} epoll_data_t;

struct epoll_event {
  uint32_t events;
  epoll_data_t data;
};
struct co_epoll_res {
  int size;
  struct epoll_event *events;
  struct kevents *eventlist;
};
int co_epoll_wait(int epfd, struct co_epoll_res *events, int maxevents,
                  int timeout);
int co_epoll_ctl(int epfd, int op, int fd, struct epoll_event *);
int epoll_create(int size);
struct co_epoll_res *co_epoll_res_alloc(int n);
void co_epoll_res_free(struct co_epoll_res *);

#endif
#endif
