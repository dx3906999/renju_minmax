#include "evaluate.h"
#include "global.h"
#include "referee.h"
#include <math.h>

enum CHESS_VALUE {
    forbidden = 0,
    five = 1000000,
    four_open = 900000,
    four_half = 100000,
    three_open = 50000,
    three_half = 10000,
    two_open = 5000,
    two_half = 1000,
    one_open = 50,
    one_half = 10
};

value_t evaluate_chess_shape(player_t player, chess_shape_t chess_shape){
    value_t score = 0;
    if (player==BLACK)
    {
        if (GET_TF_S(chess_shape))
        {
            score = forbidden;
        }
        else
        {
            score+=five*GET_SHAPE_S(chess_shape,FIVE_S);
            score+=four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S);
            score+=four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S);
            score+=three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S);
            score+=three_half*GET_SHAPE_S(chess_shape,THREE_HALF_S);
            score+=two_open*GET_SHAPE_S(chess_shape,TWO_OPEN_S);
            score+=two_half*GET_SHAPE_S(chess_shape,TWO_HALF_S);
            score+=one_open*GET_SHAPE_S(chess_shape,ONE_OPEN_S);
            score+=one_half*GET_SHAPE_S(chess_shape,ONE_HALF_S);
        }
        
        
    }
    else
    {
        score+=five*GET_SHAPE_S(chess_shape,FIVE_S);
        score+=five*GET_SHAPE_S(chess_shape,OVERLINE_S);
        score+=four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S);
        score+=four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S);
        score+=three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S);
        score+=three_half*GET_SHAPE_S(chess_shape,THREE_HALF_S);
        score+=two_open*GET_SHAPE_S(chess_shape,TWO_OPEN_S);
        score+=two_half*GET_SHAPE_S(chess_shape,TWO_HALF_S);
        score+=one_open*GET_SHAPE_S(chess_shape,ONE_OPEN_S);
        score+=one_half*GET_SHAPE_S(chess_shape,ONE_HALF_S);
        
    }
    
    return score;
    
}



void evaluate_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player, value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]){
    int chess_state[8][15]={0};
    chess_shape_t chess_shape[4]={0};
    chess_shape_t chess_shape_sum=0;
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            if (chessboard[i][j]== EMPTY)
            {
                scan_chess_state(chessboard,i,j,chess_state,player);
                analyze_chess_state(chess_state,chess_shape,chessboard,i,j,player);
                chess_shape_sum=chess_shape[0]+chess_shape[1]+chess_shape[2]+chess_shape[3];
                if (player==BLACK)
                {
                    chess_shape_sum=(GET_SHAPE_S(chess_shape_sum,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum,THREE_OPEN_S)>=2)?(chess_shape_sum&TRUE_S):(chess_shape_sum);
                }
                
                score_board_output[i][j]=evaluate_chess_shape(player,chess_shape_sum);
            }
            else
            {
                score_board_output[i][j]=0;
            }
            
        }
        
    }

    score_pos_distribution(score_board_output,CHESSBOARD_LEN/2,CHESSBOARD_LEN/2,100,1);
    
}

void score_pos_distribution(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int i_center, int j_center, value_t center_value, value_t damping){
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            score_board_output[i][j]+=MAX(0,(center_value-damping*(abs(i-i_center)+abs(j-j_center))));
        }
        
    }
    
}

void evaluate_chess_state(int chess_state[8][15],chess_shape_t chess_shape_state[4],player_t chessboard[15][15],int i,int j,player_t player){
    
}
