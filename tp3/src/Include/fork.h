#ifndef FORK_H
#define FORK_H

#include <time.h>
#include <sys/time.h>

#define NB_CHANGES 50

int fork_gettimeofday(struct timeval *tv);

int fork_clock_gettime(struct timespec *ts);

int fork_context_gettimeofday(struct timeval *tv);

int fork_context_clock_gettime(struct timespec *ts);

#endif
