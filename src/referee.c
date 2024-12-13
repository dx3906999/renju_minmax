#include <stdlib.h>
#include <stdio.h>
#include "referee.h"
#include "global.h"
#include "renju.h"

// typedef enum chess_shape_state_t{
//     TOOLONG=1,
//     FIVE,
//     FOUR_FAKE,
//     FOUR_REAL,
//     THREE_FAKE,
//     THREE_REAL
// }chess_shape_state_t;


#ifdef REFEREE_DEBUG
int bt_depth=0;
#endif



/**
 * @brief ���ֳ��򣬿����ڵݹ�
 * 
 * @param chessboard 
 * @param i 
 * @param j 
 * @param h_direction_last last half direction Ϊ-1ʱΪ�������жϣ�-2���ظ�����Ϣ
 * @return chess_shape_t 
 */
chess_shape_t is_banned(player_t chessboard[15][15],int i,int j,int h_direction_last){
    
    int chess_state[8][15]={0};
    chess_shape_t chess_shape_state[4]={0};
    int chess_shape_sum=0;
    player_t temp_chess=chessboard[i][j];
    scan_chess_state(chessboard,i,j,chess_state,BLACK);

    #ifdef REFEREE_DEBUG
    referee_debug(chessboard,i,j,chess_state);
    
    #endif

    analyze_chess_state(chess_state,chess_shape_state,chessboard,i,j,BLACK);

    
    for (size_t h_direction = 0; h_direction < 4; h_direction++)
    {
        chess_shape_sum+=chess_shape_state[h_direction];
    }
    
    /* if (GET_SHAPE_S(chess_shape_sum,FIVE_S))// �ú�һ������֣�
    {
        return false;
    }
    else if (GET_SHAPE_S(chess_shape_sum,OVERLINE_S))
    {
        return (h_direction_last==-1)?(true):chess_shape_state[h_direction_last];
    }
    else if (GET_SHAPE_S(chess_shape_sum,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum,FOUR_OPEN_S)>=2)
    {
        return (h_direction_last==-1)?(true):chess_shape_state[h_direction_last];
    }
    else if (GET_SHAPE_S(chess_shape_sum,THREE_OPEN_S)>=2)
    {
        return (h_direction_last==-1)?(true):chess_shape_state[h_direction_last];
    }
    else
    {
        return false;
    } */
    
    if (h_direction_last==-1)
    {
        chessboard[i][j]=temp_chess;
        if (GET_SHAPE_S(chess_shape_sum,FIVE_S))
        {
            return false;
        }
        else if (GET_SHAPE_S(chess_shape_sum,OVERLINE_S))
        {
            return true;
        }
        else if (GET_SHAPE_S(chess_shape_sum,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum,FOUR_OPEN_S)>=2)
        {
            return true;
        }
        else if (GET_SHAPE_S(chess_shape_sum,THREE_OPEN_S)>=2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (h_direction_last==-2)
    {
        if (GET_SHAPE_S(chess_shape_sum,FIVE_S))
        {
            return chess_shape_sum;
        }
        else if (GET_SHAPE_S(chess_shape_sum,OVERLINE_S))
        {
            return chess_shape_sum|TRUE_S;
        }
        else if (GET_SHAPE_S(chess_shape_sum,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum,FOUR_OPEN_S)>=2)
        {
            return chess_shape_sum|TRUE_S;
        }
        else if (GET_SHAPE_S(chess_shape_sum,THREE_OPEN_S)>=2)
        {
            return chess_shape_sum|TRUE_S;
        }
        else
        {
            return chess_shape_sum;
        }
    }
    else
    {
        if (GET_SHAPE_S(chess_shape_sum,FIVE_S))
        {
            return chess_shape_state[h_direction_last];
        }
        else if (GET_SHAPE_S(chess_shape_sum,OVERLINE_S))
        {
            return chess_shape_state[h_direction_last]|TRUE_S;
        }
        else if (GET_SHAPE_S(chess_shape_sum,FOUR_HALF_S)+GET_SHAPE_S(chess_shape_sum,FOUR_OPEN_S)>=2)
        {
            return chess_shape_state[h_direction_last]|TRUE_S;
        }
        else if (GET_SHAPE_S(chess_shape_sum,THREE_OPEN_S)>=2)
        {
            return chess_shape_state[h_direction_last]|TRUE_S;
        }
        else
        {
            return chess_shape_state[h_direction_last];
        }
    }
    
    
    
}


// bool is_blocked(player_t chessboard[15][15],int i,int j){

// }

void scan_chess_state(player_t chessboard[15][15],int i,int j,int chess_state[8][15],player_t player){
    int empty_index=1;
    int connected_index=0;
    // int block_num=0;
    // int connection_state=1;
    int chess_state_index=0;

    for (size_t direction = 0; direction < 8; direction++)
    {
        empty_index=1;
        connected_index=0;
        chess_state_index=0;// ��ʵ�ϣ����ûʲô��
        // block_num=0;
        // connection_state=1;
        // chess_state_index=0;
        if (!IS_IN_CHESSBOARD(i,j,1,direction))
        {
            chess_state[direction][0]=-1;
        }
        

        for (size_t k = 1; k < 15 && IS_IN_CHESSBOARD(i,j,k,direction); k++)
        {
            if (chessboard[i+i_direction[direction]*k][j+j_direction[direction]*k]==player)
            {
                chess_state[direction][connected_index]++;
                if (IS_IN_CHESSBOARD(i,j,k+1,direction)&&chessboard[i+i_direction[direction]*(k+1)][j+j_direction[direction]*(k+1)]==EMPTY)
                {
                    connected_index+=2;
                    chess_state_index++;
                }
                else if (!IS_IN_CHESSBOARD(i,j,k+1,direction)||(IS_IN_CHESSBOARD(i,j,k+1,direction)&&chessboard[i+i_direction[direction]*(k+1)][j+j_direction[direction]*(k+1)]==-player))
                {
                    // chess_state_index++;
                    chess_state[direction][connected_index+1]=-1;
                    break;
                }
                
            }
            else if (chessboard[i+i_direction[direction]*k][j+j_direction[direction]*k]==EMPTY)
            {
                chess_state[direction][empty_index]++;
                if (IS_IN_CHESSBOARD(i,j,k+1,direction)&&chessboard[i+i_direction[direction]*(k+1)][j+j_direction[direction]*(k+1)]==player)
                {
                    empty_index+=2;
                    chess_state_index++;
                }
                else if (!IS_IN_CHESSBOARD(i,j,k+1,direction)||(IS_IN_CHESSBOARD(i,j,k+1,direction)&&chessboard[i+i_direction[direction]*(k+1)][j+j_direction[direction]*(k+1)]==-player))
                {
                    chess_state[direction][empty_index+1]=-1;
                    break;
                }
                
                if (k==1)
                {
                    connected_index+=2;

                }
                
                
            }
            else
            {
                chess_state[direction][chess_state_index]=-1;
                break;
            }
            
            
        }
        
    }
    
}


void analyze_chess_state(int chess_state[8][15],chess_shape_t chess_shape_state[4],player_t chessboard[15][15],int i,int j,player_t player){
    chess_shape_t advanced_chess_shape=0;
    int four_check_num=0;
    player_t temp_chess=chessboard[i][j];
    
    for (size_t h_direction = 0; h_direction < 4; h_direction++)
    {
        if (chess_state[h_direction*2][0]>=0&&chess_state[h_direction*2+1][0]>=0)// ���߶�û��block
        {

            switch (chess_state[h_direction*2][0]+chess_state[h_direction*2+1][0]+1)
            {
            case 5:
                chess_shape_state[h_direction]|=FIVE_S;
                return;
                break;
            case 9:
                if (chess_state[h_direction*2][0]==4)
                {
                    chess_shape_state[h_direction]|=FIVE_S;
                }
                else
                {
                    chess_shape_state[h_direction]|=OVERLINE_S;
                }

                return;
                break;

            case 4:// ����������ֵĻ���ֻ��Ҫ�������ľ���
                int unblocked_num=0;

                if (player==BLACK)
                {
                    chessboard[i][j]=player;

                    if (chess_state[h_direction*2][1]>0&&(!is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),-1)))
                    {
                        unblocked_num++;
                    }

                    if (chess_state[h_direction*2+1][1]>0&&(!is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),-1)))
                    {
                        unblocked_num++;
                    }

                    chessboard[i][j]=temp_chess;// һ��Ҫ�Ļ���
                }
                else
                {
                    if (chess_state[h_direction*2][1]>0)
                    {
                        unblocked_num++;
                    }

                    if (chess_state[h_direction*2+1][1]>0)
                    {
                        unblocked_num++;
                    }
                    
                    
                }
                
                

                switch (unblocked_num)
                {
                case 2:
                    chess_shape_state[h_direction]+=FOUR_OPEN_S;
                    break;
                case 1:
                    chess_shape_state[h_direction]+=FOUR_HALF_S;
                    break;
                default:
                    break;
                }
                
                
                break;

            case 3:
                four_check_num=0;

                if (player==BLACK)
                {
                    chessboard[i][j]=player;

                    if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==1&&(!is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),-1)))
                    {
                        four_check_num++;
                    }
                    if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==1&&(!is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),-1)))
                    {
                        four_check_num++;
                    }

                    chessboard[i][j]=temp_chess;
                }
                else
                {
                    if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==1)
                    {
                        four_check_num++;
                    }
                    if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==1)
                    {
                        four_check_num++;
                    }
                    
                }

                chess_shape_state[h_direction]+=FOUR_HALF_S*four_check_num;

                if (player==BLACK)
                {
                    chessboard[i][j]=player;// ���ڻ���ֻ���� eOOOOe ����ֻ��Ҫ�ж��ٽ���λ���Ӻ��Ƿ�Ϊ����
                    if (chess_state[h_direction*2][1]>=1&&chess_state[h_direction*2+1][1]>=1)//THREE_OPEN_S
                    {
                        chess_shape_t advanced_chess_shape=0;

                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                            goto case_3_end;
                        }
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                            goto case_3_end;
                        }

                    }
                    else if (chess_state[h_direction*2][1]>=1&&chess_state[h_direction*2+1][1]==-1)//THREE_HALF_S
                    {
                        advanced_chess_shape=0;
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                            goto case_3_end;
                        }
                        
                    }
                    else if (chess_state[h_direction*2][1]==-1&&chess_state[h_direction*2+1][1]>=1)//THREE_HALF_S
                    {
                        advanced_chess_shape=0;
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                            goto case_3_end;
                        }
                    }
                    
                    
                }
                else
                {
                    if (chess_state[h_direction*2][1]>=1&&chess_state[h_direction*2+1][1]>=1)
                    {
                        chess_shape_state[h_direction]+=THREE_OPEN_S;
                    }
                    else if ((chess_state[h_direction*2][1]>=1&&chess_state[h_direction*2+1][1]==-1)||(chess_state[h_direction*2][1]==-1&&chess_state[h_direction*2+1][1]>=1))
                    {
                        chess_shape_state[h_direction]+=THREE_HALF_S;
                    }
                    
                }
                
                
                
                case_3_end:
                chessboard[i][j]=temp_chess;
                break;
                
            case 2:// ^ �������γ�һ������һ����������ֻ����һ������һ�������������Ļ�Ҳ�����ж�����������������޹�
                four_check_num=0;

                //FOUR
                if (player==BLACK)
                {
                    chessboard[i][j]=player;

                    if (
                        chess_state[h_direction*2][1]==1 &&
                        chess_state[h_direction*2][2]==2 &&
                        (!is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),-1))
                    )
                    {
                        four_check_num++;
                    }
                    if (
                        chess_state[h_direction*2+1][1]==1 &&
                        chess_state[h_direction*2+1][2]==2 &&
                        (!is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),-1))
                    )
                    {
                        four_check_num++;
                    }

                    chessboard[i][j]=temp_chess;

                    chess_shape_state[h_direction]+=FOUR_HALF_S*four_check_num;
                }
                else
                {
                    if (
                        chess_state[h_direction*2][1]==1 &&
                        chess_state[h_direction*2][2]==2 
                    )
                    {
                        four_check_num++;
                    }
                    if (
                        chess_state[h_direction*2+1][1]==1 &&
                        chess_state[h_direction*2+1][2]==2 
                    )
                    {
                        four_check_num++;
                    }

                    switch (four_check_num)
                    {
                    case 2:
                        chess_shape_state[h_direction]+=FOUR_OPEN_S;
                        break;
                    case 1:
                        chess_shape_state[h_direction]+=FOUR_HALF_S;
                        break;
                    default:
                        break;
                    }
                }
                

                //TODO: �����жϣ����Ƿ�Ϊ����
                if (player==BLACK)
                {
                    chessboard[i][j]=player;
                    if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==1)
                    {
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                            goto case_2_three_end;
                        }
                        else if (GET_SHAPE_S(advanced_chess_shape,FOUR_HALF_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                            goto case_2_three_end;
                        }
                        

                    }
                    if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==1)
                    {
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                            goto case_2_three_end;
                        }
                        else if (GET_SHAPE_S(advanced_chess_shape,FOUR_HALF_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                            goto case_2_three_end;
                        }
                        

                    }
                
                }
                else
                {
                    if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==1)
                    {
                        if ((chess_state[h_direction*2][3]==-1&&chess_state[h_direction*2+1][1]>0)||(chess_state[h_direction*2][3]>0&&chess_state[h_direction*2+1][1]==-1))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                        }
                        else if (chess_state[h_direction*2][3]>0&&chess_state[h_direction*2+1][1]>0)
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                        }
                    }
                    else if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==1)
                    {
                        if ((chess_state[h_direction*2+1][3]==-1&&chess_state[h_direction*2][1]>0)||(chess_state[h_direction*2+1][3]>0&&chess_state[h_direction*2][1]==-1))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                        }
                        else if (chess_state[h_direction*2+1][3]>0&&chess_state[h_direction*2][1]>0)
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                        }
                    }
                }
                

                case_2_three_end:
                chessboard[i][j]=temp_chess;

                //TODO:TWO
                // if (player==BLACK)
                // {
                //     // ^ �б�Ҫ��
                //     chessboard[i][j]=player;
                //     if (chess_state[h_direction*2][1]>0&&chess_state[h_direction*2+1][1]>0)
                //     {
                //         advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),h_direction);
                //         if (GET_SHAPE_S(advanced_chess_shape,THREE_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                //         {
                //             chess_shape_state[h_direction]+=TWO_OPEN_S;
                //             goto case_2_end;
                //         }
                //         else if (GET_SHAPE_S(advanced_chess_shape,THREE_HALF_S)&&(!GET_TF_S(advanced_chess_shape)))
                //         {
                //             chess_shape_state[h_direction]+=TWO_HALF_S;
                //             goto case_2_end;
                //         }
                        
                //         advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),h_direction);
                //         if (GET_SHAPE_S(advanced_chess_shape,THREE_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                //         {
                //             chess_shape_state[h_direction]+=TWO_OPEN_S;
                //             goto case_2_end;
                //         }
                //         else if (GET_SHAPE_S(advanced_chess_shape,THREE_HALF_S)&&(!GET_TF_S(advanced_chess_shape)))
                //         {
                //             chess_shape_state[h_direction]+=TWO_HALF_S;
                //             goto case_2_end;
                //         }
                        
                //     }
                //     else if (chess_state[h_direction*2][1]>0&&chess_state[h_direction*2+1][1]==-1&&!is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),-1))
                //     {
                //         chess_shape_state[h_direction]+=TWO_HALF_S;
                //         goto case_2_end;
                //     }
                //     else if (chess_state[h_direction*2][1]==-1&&chess_state[h_direction*2+1][1]>0&&!is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),-1))
                //     {
                //         chess_shape_state[h_direction]+=TWO_HALF_S;
                //         goto case_2_end;
                //     }
                    
                    
                    
                // }
                // else
                // {
                //     if (chess_state[h_direction*2][1]>0&&chess_state[h_direction*2+1][1]>0)
                //     {
                //         chess_shape_state[h_direction]+=TWO_OPEN_S;
                //     }
                //     else if ((chess_state[h_direction*2][1]>=1&&chess_state[h_direction*2+1][1]==-1)||(chess_state[h_direction*2][1]==-1&&chess_state[h_direction*2+1][1]>=1))
                //     {
                //         chess_shape_state[h_direction]+=TWO_HALF_S;
                //     }
                    
                    
                // }

                if (chess_state[h_direction*2][1]>0&&chess_state[h_direction*2+1][1]>0)
                {
                    chess_shape_state[h_direction]+=TWO_OPEN_S;
                }
                else if ((chess_state[h_direction*2][1]>=1&&chess_state[h_direction*2+1][1]==-1)||(chess_state[h_direction*2][1]==-1&&chess_state[h_direction*2+1][1]>=1))
                {
                    chess_shape_state[h_direction]+=TWO_HALF_S;
                }
                
                // case_2_end:
                chessboard[i][j]=temp_chess;
                break;
            //TODO: 
            case 1:// ^ ͬ��Ҳ�������γ�һ������һ��������������ֻ������������Ϊ������
                four_check_num=0;

                //FOUR
                if (player==BLACK)
                {
                    chessboard[i][j]=player;

                    if (
                        chess_state[h_direction*2][1]==1 &&
                        chess_state[h_direction*2][2]==3 &&
                        (!is_banned(chessboard,i+i_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),j+j_direction[h_direction*2]*(chess_state[h_direction*2][0]+1),-1))
                    )
                    {
                        four_check_num++;
                    }
                    if (
                        chess_state[h_direction*2+1][1]==1 &&
                        chess_state[h_direction*2+1][2]==3 &&
                        (!is_banned(chessboard,i+i_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),j+j_direction[h_direction*2+1]*(chess_state[h_direction*2+1][0]+1),-1))
                    )
                    {
                        four_check_num++;
                    }

                    chessboard[i][j]=temp_chess;
                    chess_shape_state[h_direction]+=FOUR_HALF_S*four_check_num;
                }
                else
                {
                    if (chess_state[h_direction*2][1]==1 && chess_state[h_direction*2][2]==3)
                    {
                        four_check_num++;
                    }
                    if (chess_state[h_direction*2+1][1]==1 && chess_state[h_direction*2+1][2]==3)
                    {
                        four_check_num++;
                    }

                    switch (four_check_num)
                    {
                    case 2:
                        chess_shape_state[h_direction]+=FOUR_OPEN_S;
                        break;
                    case 1:
                        chess_shape_state[h_direction]+=FOUR_HALF_S;
                        break;
                    default:
                        break;
                    }
                    
                }
                
                //TODO: �����ж�

                if (player==BLACK)
                {
                    chessboard[i][j]=player;

                    if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==2)
                    {
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2]*(1),j+j_direction[h_direction*2]*(1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                            goto case_1_end;
                        }
                        else if (GET_SHAPE_S(advanced_chess_shape,FOUR_HALF_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                            goto case_1_end;
                        }
                        

                    }
                    if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==2)
                    {
                        advanced_chess_shape=is_banned(chessboard,i+i_direction[h_direction*2+1]*(1),j+j_direction[h_direction*2+1]*(1),h_direction);
                        if (GET_SHAPE_S(advanced_chess_shape,FOUR_OPEN_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                            goto case_1_end;
                        }
                        else if (GET_SHAPE_S(advanced_chess_shape,FOUR_HALF_S)&&(!GET_TF_S(advanced_chess_shape)))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                            goto case_1_end;
                        }
                    }
                }
                else
                {
                    if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==2)
                    {
                        if ((chess_state[h_direction*2][3]==-1&&chess_state[h_direction*2+1][1]>0)||(chess_state[h_direction*2][3]>0&&chess_state[h_direction*2+1][1]==-1))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                        }
                        else if (chess_state[h_direction*2][3]>0&&chess_state[h_direction*2+1][1]>0)
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;// ^ ������� eOOeOeOOe ������������
                        }
                    }
                    else if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==2)// ^ ���else����ӣ����� THREE_OPEN_S ������
                    {
                        if ((chess_state[h_direction*2+1][3]==-1&&chess_state[h_direction*2][1]>0)||(chess_state[h_direction*2+1][3]>0&&chess_state[h_direction*2][1]==-1))
                        {
                            chess_shape_state[h_direction]+=THREE_HALF_S;
                        }
                        else if (chess_state[h_direction*2+1][3]>0&&chess_state[h_direction*2][1]>0)
                        {
                            chess_shape_state[h_direction]+=THREE_OPEN_S;
                        }
                    }
                    
                }
                
                //^ ��2�ж�

                //^ �Ȳ����ֿ���
                if (chess_state[h_direction*2][1]==1&&chess_state[h_direction*2][2]==1)
                {
                    if ((chess_state[h_direction*2][3]<0&&chess_state[h_direction*2+1][1]>0)||(chess_state[h_direction*2][3]>0&&chess_state[h_direction*2+1][1]<0))
                    {
                        chess_shape_state[h_direction]+=TWO_HALF_S;
                    }
                    else if (chess_state[h_direction*2][3]>0&&chess_state[h_direction*2+1][1]>0)
                    {
                        chess_shape_state[h_direction]+=THREE_OPEN_S;
                    }
                    
                }
                else if (chess_state[h_direction*2+1][1]==1&&chess_state[h_direction*2+1][2]==1)
                {
                    if ((chess_state[h_direction*2+1][3]<0&&chess_state[h_direction*2][1]>0)||(chess_state[h_direction*2+1][3]>0&&chess_state[h_direction*2][1]<0))
                    {
                        chess_shape_state[h_direction]+=TWO_HALF_S;
                    }
                    else if (chess_state[h_direction*2+1][3]>0&&chess_state[h_direction*2][1]>0)
                    {
                        chess_shape_state[h_direction]+=THREE_OPEN_S;
                    }
                }
                
                

                case_1_end:
                chessboard[i][j]=temp_chess;
                break;
            
            default:
                chess_shape_state[h_direction]|=OVERLINE_S;
                return;
                break;
            }
            
            
            
        }
        else if (chess_state[h_direction*2][0]==-1&&chess_state[h_direction*2+1][0]==-1)
        {
            continue;
        }
        else// ��һ����block
        {
            int direction_unblocked=0;
            direction_unblocked=(chess_state[h_direction*2][0]==-1)?(h_direction*2+1):(h_direction*2);

            if (chess_state[direction_unblocked][0]+1>5)
            {
                chess_shape_state[h_direction]|=OVERLINE_S;
                break;
            }
            else if (chess_state[direction_unblocked][0]+1==5)
            {
                chess_shape_state[h_direction]|=FIVE_S;
                break;
            }
            else if (chess_state[direction_unblocked][0]+1==4)
            {
                if (player==BLACK)
                {
                    chessboard[i][j]=player;
                    if (chess_state[direction_unblocked][1]>0||(!is_banned(chessboard,i+i_direction[direction_unblocked]*4,j+j_direction[direction_unblocked]*4,-1)))
                    {
                        chess_shape_state[h_direction]+=FOUR_HALF_S;
                    }
                    chessboard[i][j]=temp_chess;
                }
                else
                {
                    if (chess_state[direction_unblocked][1]>0)
                    {
                        chess_shape_state[h_direction]+=FOUR_HALF_S;
                    }
                    
                }
                
            }
            else if (chess_state[direction_unblocked][0]+1==3)
            {
                if (player==BLACK)
                {
                    chessboard[i][j]=player;
                    if (chess_state[direction_unblocked][1]>0||(!is_banned(chessboard,i+i_direction[direction_unblocked]*4,j+j_direction[direction_unblocked]*4,-1)))
                    {
                        chess_shape_state[h_direction]+=THREE_HALF_S;
                    }
                    chessboard[i][j]=temp_chess;
                }
                else
                {
                    if (chess_state[direction_unblocked][1]>0)
                    {
                        chess_shape_state[h_direction]+=THREE_HALF_S;
                    }
                    
                }
                
            }
            else if (chess_state[direction_unblocked][0]+1==2)
            {
                if (player==BLACK)
                {
                    chessboard[i][j]=player;
                    if (chess_state[direction_unblocked][1]>0||(!is_banned(chessboard,i+i_direction[direction_unblocked]*4,j+j_direction[direction_unblocked]*4,-1)))
                    {
                        chess_shape_state[h_direction]+=TWO_HALF_S;
                    }
                    chessboard[i][j]=temp_chess;
                }
                else
                {
                    if (chess_state[direction_unblocked][1]>0)
                    {
                        chess_shape_state[h_direction]+=TWO_HALF_S;
                    }
                    
                }
                
            }
            
            
        }
        
        
        
    }
    

}


bool is_five(player_t chessboard[15][15],player_t player,int i,int j){
    int sum=0;

    for (size_t h_direction = 0; h_direction < 4; h_direction++)
    {
        for (size_t k = 1; k < 5 && IS_IN_CHESSBOARD(i,j,k,h_direction*2) && chessboard[i+i_direction[h_direction*2]*k][j+j_direction[h_direction*2]*k]==player; k++)
        {
            sum++;
        }

        for (size_t k = 1; k < 5 && IS_IN_CHESSBOARD(i,j,k,h_direction*2+1) && chessboard[i+i_direction[h_direction*2+1]*k][j+j_direction[h_direction*2+1]*k]==player; k++)
        {
            sum++;
        }
        
        if (sum>=4)
        {
            return true;
        }

        sum=0;
        
    }

    return false;
    
}


bool chessboard_is_full(player_t chessboard_data[15][15]){
    for (size_t i = 0; i < 15; i++)
    {
        for (size_t j = 0; j < 15; j++)
        {
            if (chessboard_data[i][j]==EMPTY)
            {
                return false;
            }
            
        }
        
    }

    return true;
    
}


/**
 * @brief �жϵ�ǰ������Ӯ���������������̵����
 * 
 * @param chessboard_data 
 * @param player 
 * @param i 
 * @param j 
 * @return int ������Ϊ0��һ����ʤΪ1���ڷ�����Ϊ2
 */
int is_winner(player_t chessboard_data[15][15],player_t player,int i,int j){
    int result;
    int ban_state=0;
    if (player==WHITE)  // �����޽���
    {
        result=is_five(chessboard_data,player,i,j);
    }
    else  // ���忼�ǽ���
    {
        ban_state=is_banned(chessboard_data,i,j,-1);
        if (ban_state)
        {
            result=2;
        }
        else
        {
            result=is_five(chessboard_data,player,i,j);
        }
        
        // result=(!is_banned(chessboard_data,i,j,-1))&&(is_five_in_a_row(chessboard_data,player,i,j));
        // result=is_five_in_a_row(chessboard_data,player,i,j);
    }
    return result;
}


#ifdef REFEREE_DEBUG
void referee_debug(player_t chessboard[15][15],int i_last,int j_last,int chess_state[8][15]){
    bt_depth++;
    if (bt_depth>=30)
    {
        for (size_t i = 0; i < 15; i++)
        {
            for (size_t j = 0; j < 15; j++)
            {
                if (i==i_last&&j==j_last)
                {
                    printf("%d\t",2);
                }
                else
                {
                    printf("%d\t",chessboard[i][j]);
                }
                
                
            }
            printf("\n");
            
        }
        printf("\n");
        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 15; j++)
            {
                printf("%d\t",chess_state[i][j]);
            }
            printf("\n");
            
        }
        
        printf("i,j:%d %d\n",i_last,j_last);
        exit(114514);
    }
    
}

#endif

