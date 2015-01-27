#ifndef DELTA_H
#define DELTA_H

#include <time.h>
#include <sys/time.h>

int delta_gettimeofday(struct timeval *delta);

int delta_clock_gettime(struct timespec *delta);

#endif
