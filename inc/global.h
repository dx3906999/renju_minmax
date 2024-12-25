#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#define BLACK 1
#define WHITE -1
#define EMPTY 0

// #define SIG_SAVE 114514
// #define SIG_RETRACT 114515
#define CHESSBOARD_LEN 15
#define CHESSBOARD_SIZE 225
#define MIN(x,y) (((x)>(y))?(y):(x))
#define MAX(x,y) (((x)>(y))?(x):(y))
#define OPS_PLAYER(player) (-(player))

#define NULL_ACTION 255
#define MAX_ACTIONS_IN_ONE_STEP 12
#define MAX_SEARCH_DEPTH 8
// #define MAX_EXPEND_DEPTH 10
// #define MAX_EXPEND_ACTIONS_IN_ONE_STEP 5

typedef char player_t;

typedef uint8_t action_t;


#ifdef __cplusplus
}
#endif

#endif