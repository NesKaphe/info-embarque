#include "delta.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int delta_gettimeofday(struct timeval *delta) {
  struct timeval t, t2;

  if(gettimeofday(&t, NULL) < 0)
    return -1;

  if(gettimeofday(&t2, NULL) < 0)
    return -1;

  while ((t2.tv_sec - t.tv_sec == 0) && (t2.tv_usec - t.tv_usec == 0)) {
    t.tv_sec = t2.tv_sec;
    t.tv_usec = t2.tv_usec;
    if(gettimeofday(&t2, NULL) < 0)
      return -1;
  }

  delta->tv_sec = t2.tv_sec - t.tv_sec;
  delta->tv_usec = t2.tv_usec - t.tv_usec;

  return 1;
}

int delta_clock_gettime(struct timespec *delta) {

  struct timespec t, t2;

  if(clock_gettime(CLOCK_REALTIME, &t) < 0)
    return -1;

  if(clock_gettime(CLOCK_REALTIME, &t2) < 0)
    return -1;

  while ((t2.tv_sec - t.tv_sec == 0) &&
	 (t2.tv_nsec - t.tv_nsec == 0)) {
    t.tv_sec = t2.tv_sec;
    t.tv_nsec = t2.tv_nsec;
    if(clock_gettime(CLOCK_REALTIME, &t2) < 0)
      return -1;
  }

  delta->tv_sec = t2.tv_sec - t.tv_sec;
  delta->tv_nsec = t2.tv_nsec - t.tv_nsec;
  
  return 1;
}
