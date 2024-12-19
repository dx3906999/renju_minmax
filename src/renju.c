#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <signal.h>
#include "global.h"
#include "renju.h"
#include "state.h"
#include "referee.h"
#include "evaluate.h"
#include "minmax.h"
#include "utils.h"
#include "thread_pool.h"

const int i_direction[8]={1,-1,0,0,1,-1,1,-1};
const int j_direction[8]={0,0,1,-1,1,-1,-1,1};

const wchar_t TAB_LU[]=L"©°";
const wchar_t TAB_RU[]=L"©´";
const wchar_t TAB_LD[]=L"©¸";
const wchar_t TAB_RD[]=L"©¼";
const wchar_t TAB_U[]=L"©Ð";
const wchar_t TAB_D[]=L"©Ø";
const wchar_t TAB_L[]=L"©À";
const wchar_t TAB_R[]=L"©È";
const wchar_t TAB_M[]=L"©à";
const wchar_t TAB_H[]=L"©¤";
const wchar_t BLACK_STR[]=L"¡ð";
const wchar_t WHITE_STR[]=L"¡ñ";
const wchar_t BLACK_LAST_STR[]=L"¡÷";
const wchar_t WHITE_LAST_STR[]=L"¡ø";

const char RENJU_BANNER[]=
"\x1b[1;33m"
"  ____                       _\n"
" / ___| ___  _ __ ___   ___ | | ___   _\n"
"| |  _ / _ \\| '_ ` _ \\ / _ \\| |/ / | | |\n"
"| |_| | (_) | | | | | | (_) |   <| |_| |\n"
" \\____|\\___/|_| |_| |_|\\___/|_|\\_\\\\__,_|              \x1b[1;36mby dx3qOb\x1b[0m\n\x1b[0m";

int main(int argc, char const *argv[])
{
    signal(SIG_SAVE,signal_handle);
#ifdef __linux__
    setlocale(LC_CTYPE, "zh_CN.GBK");
#elif defined(_WIN32)
    setlocale(LC_CTYPE, ".936");
#endif

    while (true)
    {
        int mode_choice=-1;
        char ch;
        printf("%s\n", RENJU_BANNER);
        printf("1.pvp\n2.pve(black ai)\n3.pve(white ai)\n4.quit\n");
        scanf("%d",&mode_choice);
        while((ch = getchar()) != '\n' && ch != EOF);
        switch (mode_choice)
        {
        case 1:
            human_vs_human();
            break;
        case 2:
            human_vs_black_ai();
            break;
        case 3:
            human_vs_white_ai();
            break;
        case 4:
            exit(0);
            break;
        case 999:
            printf("debug mode.\n");
            debug_mode();
        default:
            printf("invalid choice.\n");
            break;
        }
    
    }
    return 0;
}

void display_board(player_t chessboard[CHESSBOARD_LEN][CHESSBOARD_LEN], action_t black_last_action, action_t white_last_action){
    for (size_t i = 0; i < CHESSBOARD_LEN; i++)
    {
        if (i<=5)
        {
            printf("%u ",(unsigned int)(CHESSBOARD_LEN-i));
        }
        else
        {
            printf("%u  ",(unsigned int)(CHESSBOARD_LEN-i));
        }
        
        

        for (size_t j = 0; j < CHESSBOARD_LEN; j++)
        {
            if (chessboard[i][j]==BLACK)
            {
                printf("%ls",(i==black_last_action/CHESSBOARD_LEN&&j==black_last_action%CHESSBOARD_LEN)?(BLACK_LAST_STR):(BLACK_STR));
            }
            else if (chessboard[i][j]==WHITE)
            {
                printf("%ls",(i==white_last_action/CHESSBOARD_LEN&&j==white_last_action%CHESSBOARD_LEN)?(WHITE_LAST_STR):(WHITE_STR));
            }
            else
            {
                printf("%ls",(i==0&&j==0)?(TAB_LU):(i==0&&j==CHESSBOARD_LEN-1)?(TAB_RU):(i==CHESSBOARD_LEN-1&&j==0)?(TAB_LD):(i==CHESSBOARD_LEN-1&&j==CHESSBOARD_LEN-1)?(TAB_RD):(i==0)?(TAB_U):(i==CHESSBOARD_LEN-1)?(TAB_D):(j==0)?(TAB_L):(j==CHESSBOARD_LEN-1)?(TAB_R):(TAB_M));
            }
            
            if (j!=CHESSBOARD_LEN-1)
            {
                printf("%ls",TAB_H);
            }
            
        }

        printf("\n");
        
    }
    
    printf("   A B C D E F G H I J K L M N O\n");
}

bool get_move_input(int* i, int* j){
    bool result; // true if input is valid for chessboard, false otherwise
    // char x_char=0;
    int y_int=0;
    char ch;

    scanf("%c", &ch);
    ch=(char)toupper(ch);
    if (ch=='Q')
    {
        printf("quit game.\n");
        exit(0);
    }
    else if (ch=='W')
    {
        printf("save game.\n");
        while((ch = getchar()) != '\n' && ch != EOF);//clear the buffer
        // save
        raise(SIG_SAVE);
        // maybe use signal
        result=false;
    }
    else if (ch>='A'&&ch<='O')
    {
        *j=(int)(ch-'A');
        scanf("%d",&y_int);
        while((ch = getchar()) != '\n' && ch != EOF);//clear the buffer

        if (y_int>0&&y_int<=15)
        {
            *i=(int)(15-y_int);
            result=true;
        }
        else
        {
            printf("The second parameter should be a integer from 1 to 15.\n");
            result=false;
        }
    }
    else
    {
        printf("The first parameter should be a letter from 'a' to 'o' or 'A' to 'O'.\n");
        result=false;
        while((ch = getchar()) != '\n' && ch != EOF);//clear the buffer
    }


    return result;

}

bool check_move_input_is_valid(player_t chessboard_data[15][15],int i,int j){
    if (chessboard_data[i][j]!=EMPTY)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

void signal_handle(int signum){
    switch (signum)
    {
    case SIG_SAVE:
        printf("yes");//something
        break;
    
    default:
        break;
    }
}

void human_vs_human(){
    printf("\x1b[0m\x1b[1;32mHuman vs Human mode.\n\x1b[0m");
    printf("%ls is black and %ls is white.\n",BLACK_STR,WHITE_STR);
    State* board_state=init_state();
    bool input_state=true;
    int i_input,j_input;
    int is_winner_state=0;

    while(true){
        do
        {
            display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
            printf("Round %d:black's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,BLACK_STR,BLACK_LAST_STR);
            printf("Please input the position of your chess piece, such as 'a1' or 'A1'.\n");
            // printf("value: %" PRId64 "\n",evaluate_whole_board(board_state->chessboard,board_state->current_player));
            input_state=get_move_input(&i_input,&j_input);
            if (input_state)
            {
                input_state=check_move_input_is_valid(board_state->chessboard,i_input,j_input);
                if (input_state)
                {
                    do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
                    is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
                    if (is_winner_state==2)
                    {
                        printf("Black loses.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
                        return;
                    }
                    else if (is_winner_state==1)
                    {
                        printf("Black wins!\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
                        return;
                    }
                    else if (chessboard_is_full(board_state->chessboard))
                    {
                        printf("The chessboard is full!\nTie.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
                        return;
                    }
                    
                    
                }
                else
                {
                    printf("please enter a valid action.\n");
                }
                
                
            }
            
        } while (!input_state);

        do
        {
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            printf("Round %d:white's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,WHITE_STR,WHITE_LAST_STR);
            printf("Please input the position of your chess piece, such as 'a1' or 'A1'.\n");
            // printf("value: %" PRId64 "\n",evaluate_whole_board(board_state->chessboard,board_state->current_player));
            input_state=get_move_input(&i_input,&j_input);
            if (input_state)
            {
                input_state=check_move_input_is_valid(board_state->chessboard,i_input,j_input);
                if (input_state)
                {
                    do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
                    is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
                    if (is_winner_state)
                    {
                        printf("White won!\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
                        return;
                    }
                    else if (chessboard_is_full(board_state->chessboard))
                    {
                        printf("The chessboard is full!\nTie.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
                        return;
                    }
                    
                    
                }
                else
                {
                    printf("please enter a valid action.\n");
                }
                
                
            }
            
        } while (!input_state);
        
    }

    free(board_state);

}


void human_vs_black_ai(){
    printf("\x1b[0m\x1b[1;32mHuman vs AI (black) mode.\n\x1b[0m");
    printf("%ls is black and %ls is white.\n",BLACK_STR,WHITE_STR);
    State* board_state=init_state();
    // ScoreShapeBoard* ssboard=init_score_shape_board();
    ThreadPool* pool=init_thread_pool(MAX_ACTIONS_IN_ONE_STEP);
    bool input_state=true;
    int i_input,j_input;
    int is_winner_state=0;

    while(true){

        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
        printf("Round %d:black's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,BLACK_STR,BLACK_LAST_STR);
        if (board_state->history_actions_num==0)
        {
            i_input=CHESSBOARD_LEN/2;
            j_input=CHESSBOARD_LEN/2;
        }
        else
        {
            // action_t ai_action=choose_action(board_state,BLACK);
            // action_t ai_action=choose_action_with_iterative_deepening(board_state,BLACK);
            // action_t ai_action=choose_action_with_iterative_deepening_with_ssboard(board_state,ssboard,BLACK);
            // action_t ai_action=choose_action_sum(board_state,BLACK);
            action_t ai_action=choose_action_with_iterative_deepening_and_thread(board_state,BLACK,pool);
            i_input=ai_action/CHESSBOARD_LEN;
            j_input=ai_action%CHESSBOARD_LEN;
        }
        do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
        // do_action_and_update(board_state,i_input*CHESSBOARD_LEN+j_input,ssboard);
        printf("AI move: %c%d\n",'A'+j_input,15-i_input);
        is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
        if (is_winner_state==2)
        {
            printf("Black loses.\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            return;
        }
        else if (is_winner_state==1)
        {
            printf("Black wins!\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            return;
        }
        else if (chessboard_is_full(board_state->chessboard))
        {
            printf("The chessboard is full!\nTie.\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            return;
        }


        do
        {
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            printf("Round %d:white's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,WHITE_STR,WHITE_LAST_STR);
            printf("Please input the position of your chess piece, such as 'a1' or 'A1'.\n");
            // printf("value: %" PRId64 "\n",evaluate_whole_board(board_state->chessboard,board_state->current_player));
            input_state=get_move_input(&i_input,&j_input);
            if (input_state)
            {
                input_state=check_move_input_is_valid(board_state->chessboard,i_input,j_input);
                if (input_state)
                {
                    do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
                    // do_action_and_update(board_state,i_input*CHESSBOARD_LEN+j_input,ssboard);
                    is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
                    if (is_winner_state)
                    {
                        printf("White won!\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
                        return;
                    }
                    else if (chessboard_is_full(board_state->chessboard))
                    {
                        printf("The chessboard is full!\nTie.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
                        return;
                    }
                    
                    
                }
                else
                {
                    printf("please enter a valid action.\n");
                }
                
                
            }
            
        } while (!input_state);

    }

    free(board_state);
    threadpool_destroy(pool,0);
    // free(ssboard);

}


void human_vs_white_ai(){
    printf("\x1b[0m\x1b[1;32mHuman vs AI (white) mode.\n\x1b[0m");
    printf("%ls is black and %ls is white.\n",BLACK_STR,WHITE_STR);
    State* board_state=init_state();
    ThreadPool* pool=init_thread_pool(MAX_ACTIONS_IN_ONE_STEP);
    bool input_state=true;
    int i_input,j_input;
    int is_winner_state=0;
    // value_t score_board[CHESSBOARD_LEN][CHESSBOARD_LEN]={0};

    while(true){
        do
        {
            display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
            printf("Round %d:black's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,BLACK_STR,BLACK_LAST_STR);
            printf("Please input the position of your chess piece, such as 'a1' or 'A1'.\n");
            input_state=get_move_input(&i_input,&j_input);
            if (input_state)
            {
                input_state=check_move_input_is_valid(board_state->chessboard,i_input,j_input);
                if (input_state)
                {
                    do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
                    is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
                    if (is_winner_state==2)
                    {
                        printf("Black loses.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
                        return;
                    }
                    else if (is_winner_state==1)
                    {
                        printf("Black wins!\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
                        return;
                    }
                    else if (chessboard_is_full(board_state->chessboard))
                    {
                        printf("The chessboard is full!\nTie.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
                        return;
                    }
                    
                    
                }
                else
                {
                    printf("please enter a valid action.\n");
                }
                
                
            }
            
        } while (!input_state);

        // WHITE AI TURN
        display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
        printf("Round %d:white's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,WHITE_STR,WHITE_LAST_STR);

        // evaluate_board(board_state->chessboard,WHITE,score_board);
        // choose_max_score_pos(score_board,&i_input,&j_input);

        // action_t ai_action=choose_action(board_state,WHITE);
        // action_t ai_action=choose_action_with_iterative_deepening(board_state,WHITE);
        // action_t ai_action=choose_action_sum(board_state,WHITE);
        action_t ai_action=choose_action_with_iterative_deepening_and_thread(board_state,WHITE,pool);
        i_input=ai_action/CHESSBOARD_LEN;
        j_input=ai_action%CHESSBOARD_LEN;

        do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
        printf("AI move: %c%d\n",'A'+j_input,15-i_input);
        is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
        if (is_winner_state)
        {
            printf("White won!\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
            return;
        }
        else if (chessboard_is_full(board_state->chessboard))
        {
            printf("The chessboard is full!\nTie.\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
            return;
        }
        
    }

    free(board_state);
    threadpool_destroy(pool,0);

}


void debug_mode(){
    FILE* fp=fopen("D:\\C\\renju_minmax\\temp_history_actions.txt","r");
    State* board_state=init_state();
    restore_history_from_file(fp,board_state);
    // display_board(board_state->chessboard,(board_state->history_actions_num-2+board_state->history_actions_num%2>=0)?(board_state->history_actions[board_state->history_actions_num-2+board_state->history_actions_num%2]):(NULL_ACTION),(board_state->history_actions_num-1+board_state->history_actions_num%2>=0)?(board_state->history_actions[board_state->history_actions_num-1+board_state->history_actions_num%2]):(NULL_ACTION));
    // printf("black ai analysis:\n");
    // do_action(board_state,choose_action_with_iterative_deepening(board_state,BLACK));
    // display_board(board_state->chessboard,(board_state->history_actions_num-2+board_state->history_actions_num%2>=0)?(board_state->history_actions[board_state->history_actions_num-2+board_state->history_actions_num%2]):(NULL_ACTION),(board_state->history_actions_num-1+board_state->history_actions_num%2>=0)?(board_state->history_actions[board_state->history_actions_num-1+board_state->history_actions_num%2]):(NULL_ACTION));
    fclose(fp);

    bool input_state=true;
    int i_input,j_input;
    int is_winner_state=0;

    while(true){

        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
        printf("Round %d:black's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,BLACK_STR,BLACK_LAST_STR);
        if (board_state->history_actions_num==0)
        {
            i_input=CHESSBOARD_LEN/2;
            j_input=CHESSBOARD_LEN/2;
        }
        else
        {
            // action_t ai_action=choose_action(board_state,BLACK);
            action_t ai_action=choose_action_with_iterative_deepening(board_state,BLACK);
            // action_t ai_action=choose_action_with_iterative_deepening_with_ssboard(board_state,ssboard,BLACK);
            // action_t ai_action=choose_action_sum(board_state,BLACK);
            i_input=ai_action/CHESSBOARD_LEN;
            j_input=ai_action%CHESSBOARD_LEN;
        }
        do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
        // do_action_and_update(board_state,i_input*CHESSBOARD_LEN+j_input,ssboard);
        printf("AI move: %c%d\n",'A'+j_input,15-i_input);
        is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
        if (is_winner_state==2)
        {
            printf("Black loses.\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            return;
        }
        else if (is_winner_state==1)
        {
            printf("Black wins!\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            return;
        }
        else if (chessboard_is_full(board_state->chessboard))
        {
            printf("The chessboard is full!\nTie.\n");
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            return;
        }


        do
        {
            display_board(board_state->chessboard,(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION),(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION));
            printf("Round %d:white's (%ls %ls) turn.\n",board_state->history_actions_num/2+1,WHITE_STR,WHITE_LAST_STR);
            printf("Please input the position of your chess piece, such as 'a1' or 'A1'.\n");
            // printf("value: %" PRId64 "\n",evaluate_whole_board(board_state->chessboard,board_state->current_player));
            input_state=get_move_input(&i_input,&j_input);
            if (input_state)
            {
                input_state=check_move_input_is_valid(board_state->chessboard,i_input,j_input);
                if (input_state)
                {
                    do_action(board_state,i_input*CHESSBOARD_LEN+j_input);
                    // do_action_and_update(board_state,i_input*CHESSBOARD_LEN+j_input,ssboard);
                    is_winner_state=is_winner(board_state->chessboard,OPS_PLAYER(board_state->current_player),board_state->history_actions[board_state->history_actions_num-1]/CHESSBOARD_LEN,board_state->history_actions[board_state->history_actions_num-1]%CHESSBOARD_LEN);
                    if (is_winner_state)
                    {
                        printf("White won!\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
                        return;
                    }
                    else if (chessboard_is_full(board_state->chessboard))
                    {
                        printf("The chessboard is full!\nTie.\n");
                        display_board(board_state->chessboard,(board_state->history_actions_num-2>=0)?(board_state->history_actions[board_state->history_actions_num-2]):(NULL_ACTION),(board_state->history_actions_num-1>=0)?(board_state->history_actions[board_state->history_actions_num-1]):(NULL_ACTION));
                        return;
                    }
                    
                    
                }
                else
                {
                    printf("please enter a valid action.\n");
                }
                
                
            }
            
        } while (!input_state);

    }

    free(board_state);
}

