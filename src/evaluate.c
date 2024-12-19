#include "evaluate.h"
#include "global.h"
#include "referee.h"
#include "state.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


// enum CHESS_VALUE {
//     forbidden = 0,
//     five = 10000000,
//     four_open = 900000,
//     four_half = 100000,
//     three_open = 70000,
//     three_half = 10000,
//     two_open = 1000,
//     two_half = 100,
// };


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
            // score+=one_open*GET_SHAPE_S(chess_shape,ONE_OPEN_S);
            // score+=one_half*GET_SHAPE_S(chess_shape,ONE_HALF_S);
            if (GET_SHAPE_S(chess_shape,FOUR_HALF_S)+GET_SHAPE_S(chess_shape,THREE_OPEN_S)+GET_SHAPE_S(chess_shape,FOUR_OPEN_S)>=2)
            {
                score+=four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S);
                score+=four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S);
                score+=three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S);
            }
            
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
        // score+=one_open*GET_SHAPE_S(chess_shape,ONE_OPEN_S);
        // score+=one_half*GET_SHAPE_S(chess_shape,ONE_HALF_S);
        if (GET_SHAPE_S(chess_shape,FOUR_HALF_S)+GET_SHAPE_S(chess_shape,THREE_OPEN_S)+GET_SHAPE_S(chess_shape,FOUR_OPEN_S)>=2)
        {
            score+=four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S);
            score+=four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S);
            score+=three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S);
        }
        
    }


    

    
    return score;
    
}

value_t evaluate_chess_shape_for_all(player_t player, chess_shape_t chess_shape, bool is_self){
    value_t score = 0;
    if (player==BLACK)
    {
        if (GET_TF_S(chess_shape))
        {
            if (is_self)
            {
                score-=ops_five;
            }
            else
            {
                score+=five;
            }
            
            
        }
        else
        {
            if (is_self)
            {
                score+=five*GET_SHAPE_S(chess_shape,FIVE_S)/5;
                score+=four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S)/4;
                score+=four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S)/4;
                score+=three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S)/3;
                score+=three_half*GET_SHAPE_S(chess_shape,THREE_HALF_S)/3;
                score+=two_open*GET_SHAPE_S(chess_shape,TWO_OPEN_S)/2;
                score+=two_half*GET_SHAPE_S(chess_shape,TWO_HALF_S)/2;
            }
            else
            {
                score+=ops_five*GET_SHAPE_S(chess_shape,FIVE_S)/5;
                score+=ops_four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S)/4;
                score+=ops_four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S)/4;
                score+=ops_three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S)/3;
                score+=ops_three_half*GET_SHAPE_S(chess_shape,THREE_HALF_S)/3;
                score+=ops_two_open*GET_SHAPE_S(chess_shape,TWO_OPEN_S)/2;
                score+=ops_two_half*GET_SHAPE_S(chess_shape,TWO_HALF_S)/2;
            }
            
            
        }
        
        
    }
    else
    {
        if (is_self)
        {
            score+=five*GET_SHAPE_S(chess_shape,FIVE_S)/5;
            score+=five*GET_SHAPE_S(chess_shape,OVERLINE_S)/5;
            score+=four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S)/4;
            score+=four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S)/4;
            score+=three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S)/3;
            score+=three_half*GET_SHAPE_S(chess_shape,THREE_HALF_S)/3;
            score+=two_open*GET_SHAPE_S(chess_shape,TWO_OPEN_S)/2;
            score+=two_half*GET_SHAPE_S(chess_shape,TWO_HALF_S)/2;
        }
        else
        {
            score+=ops_five*GET_SHAPE_S(chess_shape,FIVE_S)/5;
            score+=ops_five*GET_SHAPE_S(chess_shape,OVERLINE_S)/5;
            score+=ops_four_open*GET_SHAPE_S(chess_shape,FOUR_OPEN_S)/4;
            score+=ops_four_half*GET_SHAPE_S(chess_shape,FOUR_HALF_S)/4;
            score+=ops_three_open*GET_SHAPE_S(chess_shape,THREE_OPEN_S)/3;
            score+=ops_three_half*GET_SHAPE_S(chess_shape,THREE_HALF_S)/3;
            score+=ops_two_open*GET_SHAPE_S(chess_shape,TWO_OPEN_S)/2;
            score+=ops_two_half*GET_SHAPE_S(chess_shape,TWO_HALF_S)/2;
        }
        
        
        
    }
    
    return score;
    
}


void evaluate_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player, value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]){
    int chess_state[8][15]={0};
    chess_shape_t chess_shape_player[4]={0};
    chess_shape_t chess_shape_ops[4]={0};
    chess_shape_t chess_shape_sum_player=0;
    chess_shape_t chess_shape_sum_ops=0;
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {


            if (chessboard[i][j]== EMPTY)
            {
                memset(chess_shape_player,0,sizeof(chess_shape_player));
                memset(chess_shape_ops,0,sizeof(chess_shape_ops));
                chess_shape_sum_player=0;
                chess_shape_sum_ops=0;

                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i,j,chess_state,player);
                analyze_chess_state(chess_state,chess_shape_player,chessboard,i,j,player);
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i,j,chess_state,OPS_PLAYER(player));
                analyze_chess_state(chess_state,chess_shape_ops,chessboard,i,j,OPS_PLAYER(player));
                chess_shape_sum_player=chess_shape_player[0]+chess_shape_player[1]+chess_shape_player[2]+chess_shape_player[3];
                chess_shape_sum_ops=chess_shape_ops[0]+chess_shape_ops[1]+chess_shape_ops[2]+chess_shape_ops[3];
                if (player==BLACK)
                {
                    chess_shape_sum_player=(GET_SHAPE_S(chess_shape_sum_player,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_player,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_player,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_player,THREE_OPEN_S)>=2)?(chess_shape_sum_player|TRUE_S):(chess_shape_sum_player);
                }
                else
                {
                    chess_shape_sum_ops=(GET_SHAPE_S(chess_shape_sum_ops,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_ops,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_ops,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_ops,THREE_OPEN_S)>=2)?(chess_shape_sum_ops|TRUE_S):(chess_shape_sum_ops);
                }
                
                
                score_board_output[i][j]=evaluate_chess_shape(player,chess_shape_sum_player)+evaluate_chess_shape(OPS_PLAYER(player),chess_shape_sum_ops);
            }
            else
            {
                score_board_output[i][j]=0;
            }
            
        }
        
    }

    score_pos_distribution(chessboard,score_board_output,CHESSBOARD_LEN/2,CHESSBOARD_LEN/2,20,1);
    
}


void evaluate_board_for_killer(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player, value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], chess_shape_t shape_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN][2]){
    int chess_state[8][15]={0};
    chess_shape_t chess_shape_player[4]={0};
    chess_shape_t chess_shape_ops[4]={0};
    chess_shape_t chess_shape_sum_player=0;
    chess_shape_t chess_shape_sum_ops=0;
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {


            if (chessboard[i][j]== EMPTY)
            {
                memset(chess_shape_player,0,sizeof(chess_shape_player));
                memset(chess_shape_ops,0,sizeof(chess_shape_ops));
                chess_shape_sum_player=0;
                chess_shape_sum_ops=0;

                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i,j,chess_state,player);
                analyze_chess_state(chess_state,chess_shape_player,chessboard,i,j,player);
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i,j,chess_state,OPS_PLAYER(player));
                analyze_chess_state(chess_state,chess_shape_ops,chessboard,i,j,OPS_PLAYER(player));
                chess_shape_sum_player=chess_shape_player[0]+chess_shape_player[1]+chess_shape_player[2]+chess_shape_player[3];
                chess_shape_sum_ops=chess_shape_ops[0]+chess_shape_ops[1]+chess_shape_ops[2]+chess_shape_ops[3];
                if (player==BLACK)
                {
                    chess_shape_sum_player=(GET_SHAPE_S(chess_shape_sum_player,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_player,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_player,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_player,THREE_OPEN_S)>=2)?(chess_shape_sum_player|TRUE_S):(chess_shape_sum_player);
                }
                else
                {
                    chess_shape_sum_ops=(GET_SHAPE_S(chess_shape_sum_ops,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_ops,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_ops,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_ops,THREE_OPEN_S)>=2)?(chess_shape_sum_ops|TRUE_S):(chess_shape_sum_ops);
                }
                
                shape_board_output[i][j][0]=(player==BLACK)?(chess_shape_sum_player):(chess_shape_sum_ops);
                shape_board_output[i][j][1]=(player==BLACK)?(chess_shape_sum_ops):(chess_shape_sum_player);
                score_board_output[i][j]=evaluate_chess_shape(player,chess_shape_sum_player)+evaluate_chess_shape(OPS_PLAYER(player),chess_shape_sum_ops);
            }
            else
            {
                score_board_output[i][j]=0;
            }
            
        }
        
    }

    score_pos_distribution(chessboard,score_board_output,CHESSBOARD_LEN/2,CHESSBOARD_LEN/2,20,1);
    
}


value_t evaluate_whole_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], player_t player){
    int chess_state[8][15]={0};
    chess_shape_t chess_shape_player[4]={0};
    chess_shape_t chess_shape_ops[4]={0};
    chess_shape_t chess_shape_sum_player=0;
    chess_shape_t chess_shape_sum_ops=0;
    value_t score=0;

    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {

            if (chessboard[i][j]==player)
            {
                memset(chess_shape_player,0,sizeof(chess_shape_player));
                chess_shape_sum_player=0;
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i,j,chess_state,player);
                analyze_chess_state(chess_state,chess_shape_player,chessboard,i,j,player);
                chess_shape_sum_player=chess_shape_player[0]+chess_shape_player[1]+chess_shape_player[2]+chess_shape_player[3];
                if (player==BLACK)
                {
                    chess_shape_sum_player=(GET_SHAPE_S(chess_shape_sum_player,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_player,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_player,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_player,THREE_OPEN_S)>=2)?(chess_shape_sum_player|TRUE_S):(chess_shape_sum_player);
                }
                
                
                score+=evaluate_chess_shape_for_all(player,chess_shape_sum_player,true);
            }
            else if (chessboard[i][j]==OPS_PLAYER(player))
            {
                memset(chess_shape_ops,0,sizeof(chess_shape_ops));
                chess_shape_sum_ops=0;
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i,j,chess_state,OPS_PLAYER(player));
                analyze_chess_state(chess_state,chess_shape_ops,chessboard,i,j,OPS_PLAYER(player));
                chess_shape_sum_ops=chess_shape_ops[0]+chess_shape_ops[1]+chess_shape_ops[2]+chess_shape_ops[3];
                if (player==BLACK)
                {
                    chess_shape_sum_ops=(GET_SHAPE_S(chess_shape_sum_ops,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_ops,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_ops,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_ops,THREE_OPEN_S)>=2)?(chess_shape_sum_ops|TRUE_S):(chess_shape_sum_ops);
                }

                score-=evaluate_chess_shape_for_all(OPS_PLAYER(player),chess_shape_sum_ops,false);
            }
            
            
            
        }
        
    }

    return score;

}



void score_pos_distribution(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN],value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int i_center, int j_center, value_t center_value, value_t damping){
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            if (chessboard[i][j]== EMPTY)
            {
                score_board_output[i][j]+=MAX(0,(center_value-damping*(abs(i-i_center)+abs(j-j_center))));
            }
            
        }
        
    }
    
}

value_t score_pos_distribution_single(int i_center, int j_center, int i_pos, int j_pos, value_t center_value, value_t damping){
    return (value_t)MAX(0,(center_value-damping*(abs(i_pos-i_center)+abs(j_pos-j_center))));
}

void display_score_board(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN]){
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            printf("%" PRId64 "\t",score_board_output[i][j]);
        }
        printf("\n");
    }
    
}

void choose_max_score_pos(value_t score_board_output[CHESSBOARD_LEN][CHESSBOARD_LEN], int* i_output, int* j_output){
    value_t max=0;
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            if (score_board_output[i][j]>max)
            {
                max=score_board_output[i][j];
                *i_output=i;
                *j_output=j;
            }
        }
    }
}


void update_score_shape_board(ScoreShapeBoard* score_shape_board, player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t action){
    int i_action=action/CHESSBOARD_LEN;
    int j_action=action%CHESSBOARD_LEN;
    int i_temp=0;
    int j_temp=0;
    int chess_state[8][15]={0};
    chess_shape_t chess_shape_sum_temp=0;
    chess_shape_t chess_shape_temp[4]={0};

    // init if necessary
    for (size_t i = 0; i < CHESSBOARD_SIZE; i++)
    {
        if (score_shape_board->score_board_predicted[i/CHESSBOARD_LEN][i%CHESSBOARD_LEN]!=0)
        {
            break;
        }

        if (i==CHESSBOARD_SIZE-1)
        {
            score_pos_distribution(chessboard,score_shape_board->score_board_predicted,CHESSBOARD_LEN/2,CHESSBOARD_LEN/2,20,1);
        }
    }
    
    // update self

    if (chessboard[i_action][j_action]!=EMPTY)
    {
        // memset(chess_shape_temp,0,sizeof(chess_shape_temp));
        // memset(chess_state,0,sizeof(chess_state));
        scan_chess_state(chessboard,i_action,j_action,chess_state,chessboard[i_action][j_action]);
        analyze_chess_state(chess_state,chess_shape_temp,chessboard,i_action,j_action,chessboard[i_action][j_action]);
        chess_shape_sum_temp=chess_shape_temp[0]+chess_shape_temp[1]+chess_shape_temp[2]+chess_shape_temp[3];
        if (chessboard[i_action][j_action]==BLACK)
        {
            chess_shape_sum_temp=(GET_SHAPE_S(chess_shape_sum_temp,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_temp,THREE_OPEN_S)>=2)?(chess_shape_sum_temp|TRUE_S):(chess_shape_sum_temp);
        }
        score_shape_board->shape_board[i_action][j_action][chessboard[i_action][j_action]==BLACK?0:1]=chess_shape_sum_temp;
        // ^ 根据不同的player更新分数
        score_shape_board->score_board_for_self[i_action][j_action][chessboard[i_action][j_action]==BLACK?0:1]=evaluate_chess_shape_for_all(chessboard[i_action][j_action],chess_shape_sum_temp,true);
        score_shape_board->score_board_for_ops[i_action][j_action][chessboard[i_action][j_action]==BLACK?0:1]=evaluate_chess_shape_for_all(chessboard[i_action][j_action],chess_shape_sum_temp,false);
        score_shape_board->score_board_predicted[i_action][j_action]=0;
    }
    else
    {
        // black
        // memset(chess_shape_temp,0,sizeof(chess_shape_temp));
        // memset(chess_state,0,sizeof(chess_state));
        scan_chess_state(chessboard,i_action,j_action,chess_state,BLACK);
        analyze_chess_state(chess_state,chess_shape_temp,chessboard,i_action,j_action,BLACK);
        chess_shape_sum_temp=chess_shape_temp[0]+chess_shape_temp[1]+chess_shape_temp[2]+chess_shape_temp[3];
        chess_shape_sum_temp=(GET_SHAPE_S(chess_shape_sum_temp,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_temp,THREE_OPEN_S)>=2)?(chess_shape_sum_temp|TRUE_S):(chess_shape_sum_temp);
        score_shape_board->shape_board_predicted[i_action][j_action][0]=chess_shape_sum_temp;
        score_shape_board->score_board_predicted[i_action][j_action]=evaluate_chess_shape(BLACK,chess_shape_sum_temp);
        // white
        memset(chess_shape_temp,0,sizeof(chess_shape_temp));
        memset(chess_state,0,sizeof(chess_state));
        scan_chess_state(chessboard,i_action,j_action,chess_state,WHITE);
        analyze_chess_state(chess_state,chess_shape_temp,chessboard,i_action,j_action,WHITE);
        chess_shape_sum_temp=chess_shape_temp[0]+chess_shape_temp[1]+chess_shape_temp[2]+chess_shape_temp[3];
        score_shape_board->shape_board_predicted[i_action][j_action][1]=chess_shape_sum_temp;

        score_shape_board->score_board_predicted[i_action][j_action]+=evaluate_chess_shape(WHITE,chess_shape_sum_temp);
        score_shape_board->score_board_predicted[i_action][j_action]+=score_pos_distribution_single(CHESSBOARD_LEN/2,CHESSBOARD_LEN/2,i_action,j_action,20,1);
    }

    // update score
    for (size_t direction = 0; direction < 8; direction++)
    {
        for (size_t k = 1; k<15 && IS_IN_CHESSBOARD(i_action,j_action,k,direction); k++)
        {
            i_temp=i_action+i_direction[direction]*k;
            j_temp=j_action+j_direction[direction]*k;

            // 
            if (chessboard[i_temp][j_temp]!=EMPTY)
            {
                memset(chess_shape_temp,0,sizeof(chess_shape_temp));
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i_temp,j_temp,chess_state,chessboard[i_temp][j_temp]);
                analyze_chess_state(chess_state,chess_shape_temp,chessboard,i_temp,j_temp,chessboard[i_temp][j_temp]);
                chess_shape_sum_temp=chess_shape_temp[0]+chess_shape_temp[1]+chess_shape_temp[2]+chess_shape_temp[3];
                if (chessboard[i_temp][j_temp]==BLACK)
                {
                    chess_shape_sum_temp=(GET_SHAPE_S(chess_shape_sum_temp,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_temp,THREE_OPEN_S)>=2)?(chess_shape_sum_temp|TRUE_S):(chess_shape_sum_temp);
                }

                score_shape_board->shape_board[i_temp][j_temp][chessboard[i_temp][j_temp]==BLACK?0:1]=chess_shape_sum_temp;
                // ^ 根据不同的player更新分数
                score_shape_board->score_board_for_self[i_temp][j_temp][chessboard[i_temp][j_temp]==BLACK?0:1]=evaluate_chess_shape_for_all(chessboard[i_temp][j_temp],chess_shape_sum_temp,true);
                score_shape_board->score_board_for_ops[i_temp][j_temp][chessboard[i_temp][j_temp]==BLACK?0:1]=evaluate_chess_shape_for_all(chessboard[i_temp][j_temp],chess_shape_sum_temp,false);
                score_shape_board->score_board_predicted[i_temp][j_temp]=0;
                
            }
            else
            {
                // black
                memset(chess_shape_temp,0,sizeof(chess_shape_temp));
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i_temp,j_temp,chess_state,BLACK);
                analyze_chess_state(chess_state,chess_shape_temp,chessboard,i_temp,j_temp,BLACK);
                chess_shape_sum_temp=chess_shape_temp[0]+chess_shape_temp[1]+chess_shape_temp[2]+chess_shape_temp[3];
                chess_shape_sum_temp=(GET_SHAPE_S(chess_shape_sum_temp,OVERLINE_S)||(GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum_temp,FOUR_HALF_S)>=2)||GET_SHAPE_S(chess_shape_sum_temp,THREE_OPEN_S)>=2)?(chess_shape_sum_temp|TRUE_S):(chess_shape_sum_temp);

                if (GET_TF_S(chess_shape_sum_temp)!=GET_TF_S(score_shape_board->shape_board_predicted[i_temp][j_temp][0]))
                {
                    // update that position
                    score_shape_board->shape_board_predicted[i_temp][j_temp][0]=chess_shape_sum_temp;
                    update_score_shape_board(score_shape_board,chessboard,i_temp*CHESSBOARD_LEN+j_temp);
                }
                
                score_shape_board->shape_board_predicted[i_temp][j_temp][0]=chess_shape_sum_temp;

                score_shape_board->score_board_predicted[i_temp][j_temp]=evaluate_chess_shape(BLACK,chess_shape_sum_temp);
                // white
                memset(chess_shape_temp,0,sizeof(chess_shape_temp));
                memset(chess_state,0,sizeof(chess_state));
                scan_chess_state(chessboard,i_temp,j_temp,chess_state,WHITE);
                analyze_chess_state(chess_state,chess_shape_temp,chessboard,i_temp,j_temp,WHITE);
                chess_shape_sum_temp=chess_shape_temp[0]+chess_shape_temp[1]+chess_shape_temp[2]+chess_shape_temp[3];

                score_shape_board->shape_board_predicted[i_temp][j_temp][1]=chess_shape_sum_temp;
                score_shape_board->score_board_predicted[i_temp][j_temp]+=evaluate_chess_shape(WHITE,chess_shape_sum_temp);
                score_shape_board->score_board_predicted[i_temp][j_temp]+=score_pos_distribution_single(CHESSBOARD_LEN/2,CHESSBOARD_LEN/2,i_temp,j_temp,20,1);
            }
            
            
        }
        
    }
    
    
}


value_t get_score_from_ssboard(ScoreShapeBoard* ssboard, player_t player){
    value_t score=0;
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            score+=ssboard->score_board_for_self[i][j][player==BLACK?0:1]-ssboard->score_board_for_ops[i][j][OPS_PLAYER(player)==BLACK?0:1];
        }
        
    }
    return score;
    
}


void do_action_and_update(State* state,action_t action ,ScoreShapeBoard* score_shape_board){
    do_action(state,action);
    update_score_shape_board(score_shape_board, state->chessboard, action);
}

bool undo_action_and_update(State* state,ScoreShapeBoard* score_shape_board){
    action_t last_action=(state->history_actions_num>0)?state->history_actions[state->history_actions_num-1]:NULL_ACTION;
    if (last_action!=NULL_ACTION)
    {
        undo_action(state);
        update_score_shape_board(score_shape_board, state->chessboard, last_action);
        return true;

    }
    else
    {
        return false;
    }

}

ScoreShapeBoard* init_score_shape_board(){
    ScoreShapeBoard* score_shape_board=(ScoreShapeBoard*)malloc(sizeof(ScoreShapeBoard));
    if (score_shape_board)
    {
        memset(score_shape_board,0,sizeof(ScoreShapeBoard));
    }

    return score_shape_board;
    
}

//TODO: 算杀

