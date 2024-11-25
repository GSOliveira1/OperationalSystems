#ifndef RACE_H
#define RACE_H

#define NUM_PLAYERS 5
#define POINTS_TO_WIN 100

void draw_scoreboard(int player_id, int score);
int game_simulation();
void *player(void *arg);

#endif