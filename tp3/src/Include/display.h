#ifndef DISPLAY_H
#define DISPLAY_H

//Values for the scheduling option
#define SCHEDULE_PROCESS 1
#define SCHEDULE_THREAD 2
#define SCHEDULE_ALL (SCHEDULE_PROCESS | SCHEDULE_THREAD)

//Units of measurement
#define UNIT_MICROSECONDS 1
#define UNIT_NANOSECONDS 2
#define UNIT_ALL (UNIT_MICROSECONDS | UNIT_NANOSECONDS)


void display_help();

void display_delta();

void display_fork_bench(int unit);

void display_thread_bench(int unit);

void display_context_change(int type, int unit);

#endif
