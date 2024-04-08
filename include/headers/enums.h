#ifndef ENUMS_H
#define ENUMS_H

#include "common.h"

typedef enum {
  JOSHIM_STAND_1,
  JOSHIM_RUN_1,
  JOSHIM_RUN_2,
  JOSHIM_TOTAL
} JoshimFrames;

typedef enum {
  BLOCK_TYPE_EMPTY,
  BLOCK_TYPE_GRASS,
  BLOCK_TYPE_BRICK,
} BlockType;

#endif