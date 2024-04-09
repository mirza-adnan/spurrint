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
  BLOCK_TOTAL
} BlockType;

#endif