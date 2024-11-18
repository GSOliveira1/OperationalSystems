#ifndef RACE_H
#define RACE_H

#define NUM_THREADS 5
#define REACH_LINE 1000

void print_message(const char *message);
void draw_progress(int thread_id, int progress); 
int program_execution();
void *race(void *arg);

#endif