#ifndef MINMAX_H
#define MINMAX_H
#include "global.h"
#include "evaluate.h"
#include "state.h"

void get_prob_actions(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t prob_actions_output[MAX_ACTIONS_IN_ONE_STEP], player_t player);
value_t alpha_beta_search(int depth,State* state ,value_t alpha, value_t beta, bool is_max, player_t player);
action_t choose_action(State* state, player_t player);

#endif