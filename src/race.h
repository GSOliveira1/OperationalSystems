#ifndef RACE_H
#define RACE_H

#define NUM_THREADS 5
#define REACH_LINE 10000

int program_execution();
void *race(void *arg);

#endif