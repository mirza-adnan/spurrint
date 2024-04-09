#ifndef STRUCTS_H
#define STRUCTS_H

#include "common.h"
#include "enums.h"

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
} Graphics;

typedef struct {
  int x, y, h, w, size;
  BlockType type;
} Platform;

typedef struct {
  float x, y;
  float dx, dy;
  int w, h;

  SDL_Texture* frames[JOSHIM_TOTAL_FRAMES];
  int frameCount;
  JoshimFrames currFrame;

  Platform* currPlatform;

  short lives;

  bool facingRight;
  bool slowingDown;
  bool onPlatform;
  bool hasJumped;
  bool continueJump;
  bool applyGravity;
} Joshim;

typedef struct {
  unsigned int platformCount;
  Platform platforms[100];
  SDL_Texture* textures[BLOCK_TYPE_TOTAL];
} Map;

typedef struct {
  Joshim joshim;
  unsigned int time;
  Map map;
} Game;



#endif