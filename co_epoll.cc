#include "co_epoll.h"
#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#if !defined(__APPLE__) && !defined(__FreeBSD) //*macos下则编译
int co_epoll_wait(int epfd, struct co_epoll_res *events, int maxevents,
                  int timeout) {
  return epoll_wait(epfd, events->events, maxevents,
                    timeout); //*return counts of active event
}

int co_epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev) {
  return epoll_ctl(epfd, op, fd, ev);
}
int co_epoll_create(int size) { return epoll_create(size); }
struct co_epoll_res *co_epoll_res_alloc(int n) {
  struct co_epoll_res *ptr =
      (struct co_epoll_res *)malloc(sizeof(struct co_epoll_res));
  ptr->size = n;
  ptr->events = (struct epoll_event *)calloc(1, n * sizeof(struct epoll_event));
  return ptr;
}

void co_epoll_res_free(struct co_epoll_res *ptr) {
  if (!ptr) {
    return;
  }
  if (ptr->events) {
    free(ptr->events);
    free(ptr);
  }
}
#else
class clsFdMap //* millions of fd
{
private:
  static const int row_size = 1024;
  static const int col_size = 1024;
  void *m_pp[1024];

public:
  clsFdMap() {
    memset(m_pp, 0, sizeof(m_pp)); //*初始化
  }
  ~clsFdMap() {
    for (int i = 0; i < sizeof(m_pp) / sizeof(m_pp[0]); i++) {
      if (m_pp[i]) {
        free(m_pp[i]);
        m_pp[i] = NULL;
      }
    }
  }
  inline int clear(int fd) {
    set(fd, NULL);
    return 0;
  }
  inline int set(int fd, const void *ptr) {
    int idx = fd / row_size;
    //*文件描述符出错
    if (idx < 0 || idx > (sizeof(m_pp) / sizeof(m_pp[0]))) {
      assert(__LINE__ == 0);
      return -__LINE__;
    }
    if (!m_pp[idx]) {
      m_pp[idx] = (void **)calloc(1, sizeof(void *) * col_size);
    }
    m_pp[idx][fd % col_size] = (void *)ptr;
    return 0;
  }
  inline void *get(int fd) {
    int idx = fd / row_size;
    if (idx < 0 || idx >= sizeof(m_pp) / sizeof(m_pp[0])) {
      return NULL;
    }
    void **lp = m_pp[idx];
    if (!lp) {
      return NULL;
    }

    return lp[fd % col_size];
  }
}
__thread clsFdMap *s_fd_map=NULL;
static inline
#endif
