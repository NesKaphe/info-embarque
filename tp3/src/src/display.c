#include "display.h"
#include "fork.h"
#include "thread.h"
#include "delta.h"
#include <stdio.h>

void display_context_process(int unit);
void display_context_thread(int unit);

void display_help() {
  printf("Options disponnibles : \n\n"
	 "\t-h ou --help : Affiche la liste des options disponnibles\n\n"
	 "\t-p ou --process : Affiche les mesures de temps de creation de processus\n\n"
	 "\t-t ou --thread : Affiche les mesures de temps de creation de thread\n\n"
	 "\t-s ou --scheduling <type>: Affiche les mesures de temps\n\t de changement "
	 "de contexte parmis les types : \n"
	 "\t\t process : Entre deux processus\n"
	 "\t\t thread : Entre deux threads\n"
	 "\t\t all : Tous les changements de contexte séparément\n\n"
	 "\t-d ou --delta : Affiche le plus petit intervalle de temps mesurables\n"
	 "\t par les fonctions de mesures utilisées\n\n"
	 "\t-m ou --mode <unit> : Permet de specifier l'unité de mesure\n\t parmis les unités:\n"
	 "\t\t micro : microsecondes (fonction : clock_gettime)\n"
	 "\t\t nano : nanosecondes (fonction : gettimeofday)\n"
	 "\t\t all : pour un affichage dans les deux unités\n\n");
}

void display_fork_bench(int unit) {
  struct timeval tv;
  struct timespec ts;
  
  printf("\nTest de creation de processus : \n");

  switch(unit) {
  case UNIT_ALL:
  case UNIT_MICROSECONDS:
    fork_gettimeofday(&tv);
    printf("\tAvec gettimeofday : %zd sec - %zd usec\n", tv.tv_sec, tv.tv_usec);
    if(unit != UNIT_ALL)
      break;
  case UNIT_NANOSECONDS:
    fork_clock_gettime(&ts);
    printf("\tAvec clock_gettime : %zd sec - %zd nsec\n", ts.tv_sec, ts.tv_nsec);
    break;
  }
}


void display_thread_bench(int unit) {
  struct timeval tv;
  struct timespec ts;

  printf("\nTest de creation de thread : \n");

  switch(unit) {
  case UNIT_ALL:
  case UNIT_MICROSECONDS:
    thread_gettimeofday(&tv);
    printf("\tAvec gettimeofday : %zd sec - %zd usec\n", tv.tv_sec, tv.tv_usec);
    if(unit != UNIT_ALL)
      break;
  case UNIT_NANOSECONDS:
    thread_clock_gettime(&ts);
    printf("\tAvec clock_gettime : %zd sec - %zd nsec\n", ts.tv_sec, ts.tv_nsec);
    break;
  }
}


void display_delta() {
  struct timeval tv;
  struct timespec ts;

  printf("\nAffichage Delta : \n");

  if(delta_gettimeofday(&tv) < 0) {
    fprintf(stderr, "Echec du calcul du delta de gettimeofday\n");
  }
  else {
    printf("\tgettimeofday : %zd sec - %zd usec\n", tv.tv_sec, tv.tv_usec);
  }

  if(delta_clock_gettime(&ts) < 0) {
    fprintf(stderr, "Echec du calcul du delta de clock_gettime\n");
  }
  else {
    printf("\tclock_gettime : %zd sec - %zd nsec\n", ts.tv_sec, ts.tv_nsec);
  }
}


void display_context_change(int type, int unit) {
  struct timeval tv;
  struct timespec ts;

  printf("Test de scheduling\n");
  
  switch(type) {

  case SCHEDULE_ALL:
  case SCHEDULE_PROCESS:
    printf("Entre processus\n");
    switch(unit) {

    case UNIT_ALL:
    case UNIT_MICROSECONDS:
      if(fork_context_gettimeofday(&tv) < 0)
	fprintf(stderr, "Echec changements de contexte processus");
      else
	printf("\tAvec gettimeofday : %zd sec - %zd usec\n", tv.tv_sec, tv.tv_usec);

      if(unit != UNIT_ALL)
	break;
    case UNIT_NANOSECONDS:
      if(fork_context_clock_gettime(&ts) < 0)
	fprintf(stderr, "Echec changements de contexte processus");
      else
	printf("\tAvec clock_gettime : %zd sec - %zd nsec\n", ts.tv_sec, ts.tv_nsec);
      break;
    }

    if(type != SCHEDULE_ALL)
      break;

  case SCHEDULE_THREAD:
    printf("Entre threads\n");
    switch(unit) {
    case UNIT_ALL:
    case UNIT_MICROSECONDS:
      if(thread_context_gettimeofday(&tv) < 0)
	fprintf(stderr, "Echec changements de contete threads");
      else
	printf("\tAvec gettimeofday : %zd sec - %zd usec\n", tv.tv_sec, tv.tv_usec);

      if(unit != UNIT_ALL)
	break;
    case UNIT_NANOSECONDS:
      if(thread_context_clock_gettime(&ts) < 0)
	fprintf(stderr, "Echec changements de contexte threads");
      else
	printf("\tAvec clock_gettime : %zd sec - %zd nsec\n", ts.tv_sec, ts.tv_nsec);
      break;
    }
  }
}
