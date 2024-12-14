#include <stdlib.h>

#include "minmax.h"
#include "evaluate.h"
#include "global.h"
#include "utils.h"
#include "state.h"

void get_prob_actions(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t prob_actions_output[MAX_ACTIONS_IN_ONE_STEP], player_t player){
    HeapNode heap[MAX_ACTIONS_IN_ONE_STEP]={0};
    value_t score_board[CHESSBOARD_LEN][CHESSBOARD_LEN]={0};
    evaluate_board(chessboard,player,score_board);
    int heap_size=0;
    // size_t temp_index=0;
    
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            insert_heap(heap,&heap_size,score_board[i][j],(action_t)(i*CHESSBOARD_LEN+j),MAX_ACTIONS_IN_ONE_STEP);
        }
        
    }

    qsort(heap,heap_size,sizeof(HeapNode),compare_heap_node);
    
    for (size_t i = 0; i < MAX_ACTIONS_IN_ONE_STEP; i++)
    {
        if (heap[i].value>0)
        {
            prob_actions_output[i]=heap[i].index;
        }
        else
        {
            prob_actions_output[i]=NULL_ACTION;
        }
        
        
    }
    
    
}

value_t alpha_beta_search(int depth,State* state ,value_t alpha, value_t beta, bool is_max, player_t player){
    value_t score=evaluate_whole_board(state->chessboard,player);

    if(depth==0 || state->history_actions_num==CHESSBOARD_SIZE || (state->history_actions_num>0 && is_winner(state->chessboard,OPS_PLAYER(state->current_player),state->history_actions[state->history_actions_num-1]/CHESSBOARD_LEN,state->history_actions[state->history_actions_num-1]%CHESSBOARD_LEN))){
        return score;
    }

    action_t prob_actions[MAX_ACTIONS_IN_ONE_STEP]={0};
    get_prob_actions(state->chessboard,prob_actions,player);

    if (is_max)
    {
        value_t max_value=INT64_MIN;
        for (size_t i = 0; i < MAX_ACTIONS_IN_ONE_STEP && prob_actions[i]!=NULL_ACTION; i++)
        {
            do_action(state,prob_actions[i]);
            value_t temp_value=alpha_beta_search(depth-1,state,alpha,beta,false,player);
            undo_action(state);
            max_value=MAX(max_value,temp_value);
            alpha=MAX(alpha,temp_value);
            if (beta<=alpha)
            {
                break;
            }
            
        }

        return max_value;
        
    }
    else
    {
        value_t min_value=INT64_MAX;
        for (size_t i = 0; i < MAX_ACTIONS_IN_ONE_STEP && prob_actions[i]!=NULL_ACTION; i++)
        {
            do_action(state,prob_actions[i]);
            value_t temp_value=alpha_beta_search(depth-1,state,alpha,beta,true,player);
            undo_action(state);
            min_value=MIN(min_value,temp_value);
            beta=MIN(beta,temp_value);
            if (beta<=alpha)
            {
                break;
            }

        }

        return min_value;
        
    }
    
    
}


action_t choose_action(State* state, player_t player){
    value_t best_score=INT64_MIN;
    action_t best_action=NULL_ACTION;
    action_t prob_actions[MAX_ACTIONS_IN_ONE_STEP]={0};
    get_prob_actions(state->chessboard,prob_actions,player);

    for (size_t i = 0; i < MAX_ACTIONS_IN_ONE_STEP; i++)
    {
        do_action(state,prob_actions[i]);
        value_t temp_score=alpha_beta_search(MAX_SEARCH_DEPTH-1,state,INT64_MIN,INT64_MAX,false,player);
        undo_action(state);

        if (temp_score>best_score)
        {
            best_score=temp_score;
            best_action=prob_actions[i];
        }
        
    }

    return best_action;
    
}

action_t choose_action_with_iterative_deepening(State* state, player_t player){
    value_t best_score=INT64_MIN;
    action_t best_action=NULL_ACTION;
    action_t prob_actions[MAX_ACTIONS_IN_ONE_STEP]={0};
    get_prob_actions(state->chessboard,prob_actions,player);

    for (size_t depth = 2; depth <= MAX_SEARCH_DEPTH; depth+=2)
    {
        for (size_t i = 0; i < MAX_ACTIONS_IN_ONE_STEP; i++)
        {
            do_action(state,prob_actions[i]);
            value_t temp_score=alpha_beta_search(depth-1,state,INT64_MIN,INT64_MAX,false,player);
            undo_action(state);

            if (temp_score>=five)
            {
                return prob_actions[i];
            }
            

            if (depth==MAX_SEARCH_DEPTH && temp_score>best_score)
            {
                best_score=temp_score;
                best_action=prob_actions[i];
            }

        }
    }
    
}
