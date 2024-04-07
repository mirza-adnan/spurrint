#ifndef STRUCTS_H
#define STRUCTS_H

#include "common.h"

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
} Graphics;

typedef struct {} Game;

typedef struct {
  float x, y;
  float dx, dy;
  int w,h;
  short lives;
  bool facingRight;
  bool slowingDown;
  bool onPlatform;
  bool hasJumped;
  bool continueJump;
} Cat;

#endif