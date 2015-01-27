#include "thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

//Semaphores used to synchronize the two threads for the context changes
static sem_t sem1, sem2;

/*
 * This is the main for the pthread_create benchmark
 */
static void * thread_main_nothing(void *arg) {
  //Does nothing
  return NULL;
}


static void * t2_main_context(void *arg) {
  int i;

  for(i = 0; i < 499; i++) {
    sem_wait(&sem2);
    sem_post(&sem1);
  }

  return NULL;
}

int thread_gettimeofday(struct timeval *tv) {

  pthread_t thread;
  int test;

  struct timeval begin, end;

  if(gettimeofday(&begin, NULL) < 0) {
    return -1;
  }

  test = pthread_create(&thread, NULL, thread_main_nothing, NULL);
  if(test != 0) {
    return -1;
  }

  test = pthread_join(thread, NULL);
  if(test != 0) {
    return -1;
  }

  if(gettimeofday(&end, NULL) < 0) {
    return -1;
  }

  tv->tv_sec = end.tv_sec - begin.tv_sec;
  tv->tv_usec = end.tv_usec - begin.tv_usec;
  
  return 1;
}


int thread_clock_gettime(struct timespec *ts) {

  pthread_t thread;
  int test;

  struct timespec begin, end;

  if(clock_gettime(CLOCK_REALTIME, &begin) < 0) {
    return -1;
  }
  
  test = pthread_create(&thread, NULL, thread_main_nothing, NULL);

  if(test != 0) {
    return -1;
  }

  test = pthread_join(thread, NULL);
  if(test != 0) {
    return -1;
  }

  if(clock_gettime(CLOCK_REALTIME, &end) < 0) {
    return -1;
  }

  ts->tv_sec = end.tv_sec - begin.tv_sec;
  ts->tv_nsec = end.tv_nsec - begin.tv_nsec;
  
  return 1;
}


int thread_context_gettimeofday(struct timeval *tv) {

  pthread_t t2;
  int test, i;
  struct timeval begin, end;
  suseconds_t temp = 0;

  //Semaphore initialisation
  if(sem_init(&sem1, 1, 1) < 0) //Available from begining
    return -4; //Semaphore fail

  if(sem_init(&sem2, 1, 0) < 0) //Unavailable from begining
    return -4; //Semaphore fail


  test = pthread_create(&t2, NULL, t2_main_context, NULL);

  if(test != 0) {
    return -1;
  }

  if(gettimeofday(&begin, NULL) < 0) {
    return -1;
  }

  for(i = 0; i < 499; i++) {
    sem_wait(&sem1);
    sem_post(&sem2);
  }  

  test = pthread_join(t2, NULL);
  if(test != 0) {
    return -1;
  }

  if(gettimeofday(&end, NULL) < 0) {
    return -1;
  }

  tv->tv_sec = end.tv_sec - begin.tv_sec;
  tv->tv_usec = end.tv_usec - begin.tv_usec;
  
  //Now that we have many context changes we want the time of only one
  temp = tv->tv_sec * 1000000 + tv->tv_usec;
  temp = temp / 1000;
  
  //Then we can store the final result into tv
  tv->tv_sec = (long) (temp / 1000000);
  tv->tv_usec = temp % 1000000;

  return 1;
}

int thread_context_clock_gettime(struct timespec *ts) {

  pthread_t t2;
  int test, i;
  struct timespec begin, end;
  long temp;

 //Semaphore initialisation
  if(sem_init(&sem1, 1, 1) < 0) //Available from begining
    return -4; //Semaphore fail

  if(sem_init(&sem2, 1, 0) < 0) //Unavailable from begining
    return -4; //Semaphore fail

  test = pthread_create(&t2, NULL, t2_main_context, NULL);

  if(test != 0) {
    return -1;
  }

  if(clock_gettime(CLOCK_REALTIME, &begin) < 0) {
    return -1;
  }
  
  for(i = 0; i < 499; i++) {
    sem_wait(&sem1);
    sem_post(&sem2);
  }

  test = pthread_join(t2, NULL);
  if(test != 0) {
    return -1;
  }

  if(clock_gettime(CLOCK_REALTIME, &end) < 0) {
    return -1;
  }

  ts->tv_sec = end.tv_sec - begin.tv_sec;
  ts->tv_nsec = end.tv_nsec - begin.tv_nsec;
  
  //Now that we have many context changes we want the time of only one
  temp = ts->tv_sec * 1000000 + ts->tv_nsec;
  temp = temp / 1000;
  
  //Then we can store the final result into ts
  ts->tv_sec = (long) (temp / 1000000);
  ts->tv_nsec = temp % 1000000;

  return 1;
}
