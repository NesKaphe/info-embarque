#ifndef THREAD_H
#define THREAD_H

#include <time.h>
#include <sys/time.h>

int thread_gettimeofday(struct timeval *tv);

int thread_clock_gettime(struct timespec *ts);

int thread_context_gettimeofday(struct timeval *tv);

int thread_context_clock_gettime(struct timespec *ts);

#endif
