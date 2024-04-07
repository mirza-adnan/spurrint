#ifndef STRUCTS_H
#define STRUCTS_H

#include "common.h"
#include "enums.h"

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
} Graphics;

typedef struct {
  float x, y;
  float dx, dy;
  int w,h;

  SDL_Texture* frames[4];
  int frameCount;
  JoshimFrames currFrame;

  short lives;
  bool facingRight;
  bool slowingDown;
  bool onPlatform;
  bool hasJumped;
  bool continueJump;
} Joshim;

typedef struct {
  Joshim joshim;
  unsigned int time;
} Game;



#endif