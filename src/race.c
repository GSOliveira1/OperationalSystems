#include "race.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t lock;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int winner = -1;
int game_over = 0;
time_t start_time, end_time;

int game_simulation(){
    pthread_t players[NUM_PLAYERS]; /* Array de Threads */
    int ids_players[NUM_PLAYERS];

    if (pthread_mutex_init(&lock, NULL)){
        fprintf(stderr, "Error initializing mutex.\n");
        return 1;
    }
    
    time(&start_time);

    int i;
    for (i = 0; i < NUM_PLAYERS; i++){
        ids_players[i] = i + 1;
        if (pthread_create(&players[i], NULL, player, (void *)&ids_players[i]) != 0){
            fprintf(stderr, "Fail to create players.\n");
            return 1;
        } else {
            printf("Player %d created successfully!\n", ids_players[i]);
        }
    }
    printf("\n");

    for (i = 0; i < NUM_PLAYERS; i++){
        pthread_join(players[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&condition);

    return 0;
}

void *player(void *arg){
    int score = 0;
    int id = *(int *)arg;
    // Loop responsável pela corrida:
    while (1){ 
        pthread_mutex_lock(&lock);

        if (game_over){
            pthread_mutex_unlock(&lock);
            break;
        }

        pthread_mutex_unlock(&lock);

        usleep(50000);  // Atraso fixo
        usleep(rand() % 5000);  // Simula o tempo para marcar os pontos;
        int points_scored =  (rand() % 3) + 1;  // Marca entre 1 e 3 pontos;
        score += points_scored;
        
        printf("Player %d scored %d points in total!\n", id, score);

        if (score > POINTS_TO_WIN)
            score = POINTS_TO_WIN;

        if (score >= POINTS_TO_WIN){
            pthread_mutex_lock(&lock);

            // Verifica e define o vencedor se ainda não houver um:
            if (winner == -1){
                winner = id;
                time(&end_time);
                printf("\nPlayer number %d is the winner!\n", id);
                double time_taken = difftime(end_time, start_time);
                printf("Player %d took: %.2f seconds to win!\n", id, time_taken);
                game_over = 1;
                pthread_cond_broadcast(&condition);
            }

            pthread_mutex_unlock(&lock);
            break;
        }
    }

    return NULL;
}