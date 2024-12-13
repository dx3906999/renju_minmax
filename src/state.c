#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "state.h"

State* init_state(){
    State* state=malloc(sizeof(State));
    if (state)
    {
        memset(state->chessboard, 0, sizeof(state->chessboard));
        // memset(state->actions_unavailable, 0, sizeof(state->actions_unavailable));
        state->history_actions_num = 0;
        state->current_player = BLACK;
    }

    return state;
}


void do_action(State* state,action_t action){
    state->chessboard[action/CHESSBOARD_LEN][action%CHESSBOARD_LEN]=state->current_player;
    // state->actions_unavailable[action]=true;
    state->history_actions_num++;
    state->history_actions[state->history_actions_num-1]=action;
    state->current_player=OPS_PLAYER(state->current_player);
}

bool undo_action(State* state){
    action_t last_action=(state->history_actions_num>0)?state->history_actions[state->history_actions_num-1]:NULL_ACTION;
    if (last_action!=NULL_ACTION)
    {
        state->chessboard[last_action/CHESSBOARD_LEN][last_action%CHESSBOARD_LEN]=EMPTY;
        state->history_actions_num--;
        state->current_player=OPS_PLAYER(state->current_player);
        return true;
    }
    else
    {
        return false;
    }
    
}


