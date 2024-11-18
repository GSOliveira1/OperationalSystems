#include "race.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t lock;
int winner = -1;
clock_t start_time, end_time;

int program_execution(){
    pthread_t threads[NUM_THREADS]; /* Threads array */
    int ids_threads[NUM_THREADS];

    if (pthread_mutex_init(&lock, NULL))
    {
        fprintf(stderr, "Error initializing mutex.\n");
        return 1;
    }
    
    start_time = clock();

    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        ids_threads[i] = i + 1;
        if (pthread_create(&threads[i], NULL, race, (void *)&ids_threads[i]) != 0)
        {
            fprintf(stderr, "Fail to create threads.\n");
            return 1;
        } else {
            printf("Thread %d created successfully!\n", ids_threads[i]);
        }
    }
    printf("\n");

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}

void *race(void *arg)
{
    int contador = 0;
    int id = *(int *)arg;

    for (int i = 0; i < REACH_LINE; i++)
    {
        usleep(rand() % 1000); // Simula o trabalho da thread
        contador++;

        if (contador >= REACH_LINE)
        {
            pthread_mutex_lock(&lock);

            // Verifica e define o vencedor se ainda não houver um
            if (winner == -1)
            {
                winner = id;
                end_time = clock();
                printf("Thread number %d is the winner!\n", id);

                double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
                printf("Thread %d execution time: %.6f seconds\n", id, time_taken);
            }

            pthread_mutex_unlock(&lock);
            break; // Interrompe o loop quando uma thread ganha
        }
    }

    return NULL;
}