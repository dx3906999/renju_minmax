#ifndef EVALUATE_H
#define EVALUATE_H
#include "global.h"
#include "referee.h"

typedef int64_t value_t;

value_t evaluate_chess_shape(player_t player, chess_shape_t chess_shape);
void evaluate_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player, value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]);


#endif // EVALUATE_H