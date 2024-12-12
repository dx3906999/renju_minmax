#ifndef EVALUATE_H
#define EVALUATE_H
#include "global.h"
#include "referee.h"

typedef int64_t value_t;

value_t evaluate_chess_shape(player_t player, chess_shape_t chess_shape);
value_t evaluate_chess_shape_for_all(player_t player, chess_shape_t chess_shape);
void evaluate_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player, value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]);
value_t evaluate_whole_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player);
// void score_pos_distribution(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int i_center, int j_center, value_t center_value, value_t damping);
void choose_max_score_pos(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int* i_output, int* j_output);
void display_score_board(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]);
void score_pos_distribution(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN],value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int i_center, int j_center, value_t center_value, value_t damping);
value_t score_pos_distribution_single(int i_center, int j_center, value_t center_value, value_t damping);
#endif // EVALUATE_H