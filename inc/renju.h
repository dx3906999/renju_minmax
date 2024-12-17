#ifndef RENJU_H
#define RENJU_H

#include "global.h"

extern const int i_direction[8];
extern const int j_direction[8];

void display_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t black_last_action, action_t white_last_action);
bool get_move_input(int* i, int* j);
bool check_move_input_is_valid(player_t chessboard_data[15][15],int i,int j);
void signal_handle(int signum);
void human_vs_human();
void human_vs_black_ai();
void human_vs_white_ai();
void debug_mode();
#endif