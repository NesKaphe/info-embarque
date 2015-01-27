#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"

//All the options used to detect the benchmarks needed (theses are indices for the option table)
#define PROCESS 0
#define THREAD 1
#define SCHEDULING 2
#define DELTA 3

//Total available options
#define MAX_CMD 4


int main(int argc, char **argv) {

  int i;
  char options[MAX_CMD] = {0}; //Determines wheither or not the option is enabled :  0 : option disabled, >1 : option enabled with value
  char unit = UNIT_ALL;

  if(argc < 2) {
    fprintf(stderr, "Erreur : Mauvais paramètres.\n Executez <%s -h> ou <%s --help> pour plus d'informations\n", argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }
  else {
    //getting the options to execute the programs
    for(i = 1; i < argc; i++) {
      if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
	//Show help and exit
	display_help();
	exit(EXIT_SUCCESS);
      }

      else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--process") == 0) {
	//Activate fork benchmark
	options[PROCESS] = 1;
      }

      else if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--thead") == 0) {
	//Activate thread benchmark
	options[THREAD] = 1;
      }

      else if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--scheduling") == 0) {
	//We'll check the type of scheduling wanted by user
	if(argc > i+1) {

	  if(strcmp(argv[i+1], "p") == 0 || strcmp(argv[i+1], "process") == 0) {
	    options[SCHEDULING] = SCHEDULE_PROCESS;
	  }

	  else if(strcmp(argv[i+1], "t") == 0 || strcmp(argv[i+1], "thread") == 0) {
	    options[SCHEDULING] = SCHEDULE_THREAD;
	  }

	  else if(strcmp(argv[i+1], "a") == 0 || strcmp(argv[i+1], "all") == 0) {
	    options[SCHEDULING] = SCHEDULE_ALL;
	  }

	  else {
	    fprintf(stderr,"Erreur : Paramètre [%s] inconnu pour l'option de scheduling.\n Executez <%s -h> ou <%s --help> pour plus d'informations\n", argv[i+1], argv[0], argv[0]);
	    exit(EXIT_FAILURE);
	  }

	  i++;
	}

	else {
	  fprintf(stderr,"Erreur : Paramètre manquant pour l'option de scheduling.\n Executez <%s -h> ou <%s --help> pour plus d'informations\n", argv[0], argv[0]);
	  exit(EXIT_FAILURE);
	}
      }

      else if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) {
	//We'll check the unit wanted by user
	if(argc > i+1) {

	  if(strcmp(argv[i+1], "micro") == 0) {
	    unit = UNIT_MICROSECONDS;
	  }

	  else if(strcmp(argv[i+1], "nano") == 0) {
	    unit = UNIT_NANOSECONDS;
	  }

	  else if(strcmp(argv[i+1], "a") == 0 || strcmp(argv[i+1], "all") == 0) {
	    unit = UNIT_ALL;
	  }

	  else {
	    fprintf(stderr,"Erreur : Paramètre [%s] inconnu pour le mode de benchmark.\n Executez <%s -h> ou <%s --help> pour plus d'informations\n", argv[i+1], argv[0], argv[0]);
	    exit(EXIT_FAILURE);
	  }

	  i++;
	}

	else {
	  fprintf(stderr,"Erreur : Paramètre manquant pour le mode de benchmark.\n Executez <%s -h> ou <%s --help> pour plus d'informations\n", argv[0], argv[0]);
	  exit(EXIT_FAILURE);
	}
      }

      else if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delta") == 0) {
	options[DELTA] = 1;
      }

      else {
	fprintf(stderr,"Erreur : Option [%s] inconnue.\n Executez <%s -h> ou <%s --help> pour plus d'informations\n", argv[i], argv[0], argv[0]);
	exit(EXIT_FAILURE);
      }
    }
  }
  
  //We can now execute all the options activated by the user
  if(options[DELTA]) {
    display_delta();
  }

  if(options[PROCESS]) {
    display_fork_bench(unit);
  }

  if(options[THREAD]) {
    display_thread_bench(unit);
  }

  if(options[SCHEDULING]) {
    display_context_change(options[SCHEDULING], unit);
  }

  exit(EXIT_SUCCESS);
}
