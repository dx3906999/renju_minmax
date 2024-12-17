#ifndef MINMAX_H
#define MINMAX_H
#include "global.h"
#include "evaluate.h"
#include "state.h"
#include "thread_pool.h"

typedef struct SearchArgs{
    State* state;
    value_t* score;
    int depth;
    player_t player;
    action_t action;
}SearchArgs;


void get_prob_actions(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t prob_actions_output[MAX_ACTIONS_IN_ONE_STEP], player_t player);
value_t alpha_beta_search(int depth,State* state ,value_t alpha, value_t beta, bool is_max, player_t player);
action_t choose_action(State* state, player_t player);
action_t choose_action_with_iterative_deepening(State* state, player_t player);
void get_prob_actions_from_ssboard(ScoreShapeBoard* ssboard, action_t prob_actions_output[MAX_ACTIONS_IN_ONE_STEP], player_t player);
value_t alpha_beta_search_with_ssboard(int depth,State* state, ScoreShapeBoard* ssboard,value_t alpha, value_t beta, bool is_max, player_t player);
action_t choose_action_with_iterative_deepening_with_ssboard(State* state, ScoreShapeBoard* ssboard,player_t player);
void get_prob_actions_for_killer(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t prob_actions_output[MAX_KILLER_ACTIONS_IN_ONE_STEP], player_t player);
// value_t alpha_beta_search_killer(int depth,State* state ,value_t alpha, value_t beta, bool is_max, player_t player);
value_t alpha_beta_search_for_killer(int depth,State* state ,value_t alpha, value_t beta, bool is_max, player_t player);
action_t choose_action_with_iterative_deepening_for_killer(State* state, player_t player);
action_t choose_action_sum(State* state, player_t player);
void search_one_step_with_thread(void* args);
action_t choose_action_with_iterative_deepening_and_thread(State* state, player_t player, ThreadPool* thread_pool);
#endif