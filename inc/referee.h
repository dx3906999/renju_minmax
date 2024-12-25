#ifndef REFEREE_H
#define REFEREE_H

#ifdef __cplusplus
extern "C" {
#endif

// #define REFEREE_DEBUG

#include "global.h"
#include "renju.h"
#include <stdint.h>

#define OVERLINE_S UINT64_C(1)
#define FIVE_S (UINT64_C(1)<<(4*1))
#define DEAD_S (UINT64_C(1)<<(4*2))
#define FOUR_HALF_S (UINT64_C(1)<<(4*3))
#define FOUR_OPEN_S (UINT64_C(1)<<(4*4))
#define THREE_HALF_S (UINT64_C(1)<<(4*5))
#define THREE_OPEN_S (UINT64_C(1)<<(4*6))
#define TWO_HALF_S (UINT64_C(1)<<(4*7))
#define TWO_OPEN_S (UINT64_C(1)<<(4*8))
// #define ONE_HALF_S (1<<(4*9))
// #define ONE_OPEN_S (1<<(4*10))
#define TRUE_S (UINT64_C(1)<<(sizeof(chess_shape_t)*8-1))
#define FALSE_S 0
#define GET_SHAPE_S(chess_shape_s,std_shape_s) (((chess_shape_s)&((std_shape_s)|((std_shape_s)<<1)|((std_shape_s)<<2)|((std_shape_s)<<3)))/(std_shape_s))
#define GET_TF_S(chess_shape_s) ((chess_shape_s)>>(sizeof(chess_shape_t)*8-1))


#define IS_IN_CHESSBOARD(i,j,k,direction) ((i)+i_direction[(direction)]*(k)>=0 && (i)+i_direction[(direction)]*(k)<15 && (j)+j_direction[(direction)]*(k)>=0 && (j)+j_direction[(direction)]*(k)<15)
#define THE_CHESS(chessboard,i,j,k,direction) ((chessboard)[(i)+i_direction[(direction)]*(k)][(j)+j_direction[(direction)]*(k)])

 
typedef uint64_t chess_shape_t;

chess_shape_t is_banned(player_t chessboard[15][15],int i,int j,int h_direction_last);
void scan_chess_state(player_t chessboard[15][15],int i,int j,int chess_state[8][15],player_t player);
void analyze_chess_state(int chess_state[8][15],chess_shape_t chess_shape_state[4],player_t chessboard[15][15],int i,int j,player_t player);
bool is_five(player_t chessboard[15][15],player_t player,int i,int j);
bool chessboard_is_full(player_t chessboard_data[15][15]);
int is_winner(player_t chessboard_data[15][15],player_t player,int i,int j);

#ifdef REFEREE_DEBUG
void referee_debug(player_t chessboard[15][15],int i,int j,int chess_state[8][15]);
#endif

#ifdef __cplusplus
}
#endif

#endif