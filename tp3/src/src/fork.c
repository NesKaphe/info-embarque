#include "fork.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <stdio.h>

struct shared {
  sem_t sem1;
  sem_t sem2;
};


int init_semaphores(struct shared **semaphores) {

  if((*semaphores = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE,
      MAP_SHARED | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
    return -2; //Map fail
  }

  //Then we initialize them
  if(sem_init(&( *semaphores )->sem1, 1, 1) < 0) //Available from begining
    return -4; //Semaphore fail

  if(sem_init(&( *semaphores )->sem2, 1, 0) < 0) //Unavailable from begining
    return -4; //Semaphore fail

  return 1;
}

int fork_gettimeofday(struct timeval *tv) {
  pid_t pid;
  int status;

  struct timeval begin, end;
  
  if(gettimeofday(&begin, NULL) < 0) {
    return -1;
  }

  pid = fork();
  if(pid > 0) { //parent
    wait(&status);
  }
  else if(pid == 0) { //child
    //The child will do nothing but terminate
    exit(EXIT_SUCCESS);
  }
  else {
    return -1;
  }

  if(gettimeofday(&end, NULL) < 0) {
    return -1;
  }

  tv->tv_sec = end.tv_sec - begin.tv_sec;
  tv->tv_usec = end.tv_usec - begin.tv_usec;

  return 1;
}


int fork_clock_gettime(struct timespec *ts) {
  pid_t pid;
  int status;

  struct timespec begin, end;

  if(clock_gettime(CLOCK_REALTIME, &begin) < 0) {
    return -1;
  }

  pid = fork();
  if(pid > 0) { //parent
    wait(&status);
  }
  else if(pid == 0) { //child
    //The child will do nothing but terminate
    exit(EXIT_SUCCESS);
  }
  else {
    return -1;
  }

  if(clock_gettime(CLOCK_REALTIME, &end) < 0) {
    return -1;
  }

  ts->tv_sec = end.tv_sec - begin.tv_sec;
  ts->tv_nsec = end.tv_nsec - begin.tv_nsec;

  return 1;
}


int fork_context_gettimeofday(struct timeval *tv) {

  struct shared *semaphores = NULL;
  int pid, status, i;
  struct timeval begin, end;
  suseconds_t temp = 0; //Used to calculate the time for 1 context change

  //First we have to prepare the shared semaphores between the processes
  init_semaphores(&semaphores);
  
  pid = fork();
  if(pid > 0) { //parent
    if(gettimeofday(&begin, NULL) < 0) {
      return -1;
    }
    for(i = 0; i < 499; i++) {
      sem_wait(&semaphores->sem1);
      sem_post(&semaphores->sem2);
    }

    if(gettimeofday(&end, NULL) < 0) {
      return -1;
    }
    wait(&status);
  }
  else if(pid == 0) { //child
    for(i = 0; i < 499; i++) {
      sem_wait(&semaphores->sem2);
      sem_post(&semaphores->sem1);
    }
    exit(EXIT_SUCCESS);
  }
  else {
    return -1;
  }

  if(munmap(semaphores, sizeof(struct shared)) < 0)
    return -3;

  tv->tv_sec = end.tv_sec - begin.tv_sec;
  tv->tv_usec = end.tv_usec - begin.tv_usec;

  //Now that we have many context changes we want the time of only one
  temp = tv->tv_sec * 1000000 + tv->tv_usec;
  temp = temp / 1000;
  
  //Then we can store the final result into tv
  tv->tv_sec = (suseconds_t) (temp / 1000000);
  tv->tv_usec = temp % 1000000;

  return 1;
}


int fork_context_clock_gettime(struct timespec *ts) {

  struct shared *semaphores = NULL;
  int pid, status, i;
  struct timespec begin, end;
  long temp;

  //First we have to prepare the shared semaphores between the processes
  init_semaphores(&semaphores);
  
  pid = fork();
  if(pid > 0) { //parent

    if(clock_gettime(CLOCK_REALTIME, &begin) < 0) {
      return -1;
    }

    for(i = 0; i < 499; i++) {
      sem_wait(&semaphores->sem1);
      sem_post(&semaphores->sem2);
    }
    if(clock_gettime(CLOCK_REALTIME, &end) < 0) {
      return -1;
    }
    wait(&status);
  }
  else if(pid == 0) { //child
    for(i = 0; i < 499; i++) {
      sem_wait(&semaphores->sem2);
      sem_post(&semaphores->sem1);
    }
    exit(EXIT_SUCCESS);
  }
  else {
    return -1;
  }

  if(munmap(semaphores, sizeof(struct shared)) < 0)
    return -3;

  ts->tv_sec = end.tv_sec - begin.tv_sec;
  ts->tv_nsec = end.tv_nsec - begin.tv_nsec;
  
  //Now that we have many context changes we want the time of only one
  temp = ts->tv_sec * 1000000 + ts->tv_nsec;
  temp = temp / 1000;
  
  //Then we can store the final result into tv
  ts->tv_sec = (long) (temp / 1000000);
  ts->tv_nsec = temp % 1000000;

  return 1;
}
