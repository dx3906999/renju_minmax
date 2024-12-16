#ifndef EVALUATE_H
#define EVALUATE_H
#include "global.h"
#include "referee.h"
#include "state.h"

typedef int64_t value_t;
typedef struct ScoreShapeBoard ScoreShapeBoard;

enum CHESS_VALUE {
    forbidden = 0,
    five = 50000,
    four_open = 4320,
    four_half = 720,
    three_open = 720,
    three_half = 100,
    two_open = 120,
    two_half = 20,
};

enum OPPOSITE_CHESS_VALUE {
    ops_forbidden = 0,
    ops_five = 100000,
    ops_four_open = 48000,
    ops_four_half = 38000,
    ops_three_open = 3500,
    ops_three_half = 720,
    ops_two_open = 720,
    ops_two_half = 100,
};

struct ScoreShapeBoard
{
    value_t score_board_for_self[CHESSBOARD_LEN][CHESSBOARD_LEN][2];
    value_t score_board_for_ops[CHESSBOARD_LEN][CHESSBOARD_LEN][2];
    value_t score_board_predicted[CHESSBOARD_LEN][CHESSBOARD_LEN];
    chess_shape_t shape_board[CHESSBOARD_LEN][CHESSBOARD_LEN][2];
    chess_shape_t shape_board_predicted[CHESSBOARD_LEN][CHESSBOARD_LEN][2];
};


value_t evaluate_chess_shape(player_t player, chess_shape_t chess_shape);
value_t evaluate_chess_shape_for_all(player_t player, chess_shape_t chess_shape, bool is_self);
void evaluate_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player, value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]);
value_t evaluate_whole_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player);
// void score_pos_distribution(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int i_center, int j_center, value_t center_value, value_t damping);
void choose_max_score_pos(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int* i_output, int* j_output);
void display_score_board(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]);
void score_pos_distribution(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN],value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int i_center, int j_center, value_t center_value, value_t damping);
value_t score_pos_distribution_single(int i_center, int j_center, int i_pos, int j_pos, value_t center_value, value_t damping);
void update_score_shape_board(ScoreShapeBoard* score_shape_board, player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t action);
void do_action_and_update(State* state,action_t action ,ScoreShapeBoard* score_shape_board);
bool undo_action_and_update(State* state,ScoreShapeBoard* score_shape_board);
value_t get_score_from_ssboard(ScoreShapeBoard* ssboard, player_t player);
ScoreShapeBoard* init_score_shape_board();
// value_t get_score_from_ssboard(ScoreShapeBoard* ssboard, player_t player);


#endif // EVALUATE_H