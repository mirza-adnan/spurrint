#ifndef ENUMS_H
#define ENUMS_H

#include "common.h"

typedef enum {
  JOSHIM_RUN_1,
  JOSHIM_RUN_2,
  JOSHIM_RUN_3,
  JOSHIM_IDLE_1,
  JOSHIM_IDLE_2,
  JOSHIM_IDLE_3,
  JOSHIM_JUMP_1,
  JOSHIM_TOTAL_FRAMES
} JoshimFrames;

typedef enum {
  BLOCK_TYPE_EMPTY,
  BLOCK_TYPE_GRASS,
  BLOCK_TYPE_DIRT_1,
  BLOCK_TYPE_DIRT_2,
  BLOCK_TYPE_BRICK,
  BLOCK_TYPE_CHICKEN,
  BLOCK_TYPE_TOTAL
} BlockType;

typedef enum {
  GAME_STATUS_MENU,
  GAME_STATUS_GAME,
  GAME_STATUS_END
} GameStatus;

typedef enum {
  FONT_SIZE_48,
  FONT_SIZE_TOTAL
} FontSize;

#endif