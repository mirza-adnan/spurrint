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
  bool touched;
} Platform;

typedef struct {
  float x, y;
  float dx, dy;
  int w, h;

  unsigned int score;

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
  float x, y;
  int w, h;
  bool collected;
} Collectible;

typedef struct {
  unsigned int platformCount;
  Platform platforms[50];
  unsigned int collectibleCount;
  Collectible collectibles[20];
  SDL_Texture* textures[BLOCK_TYPE_TOTAL];
  SDL_Texture* buildings[2];
} Map;

typedef struct {
  TTF_Font* fonts[FONT_SIZE_TOTAL];
  SDL_Texture* scoreLabel;
} Text;

typedef struct {
  char name[10];
  int x, y, w, h;
  bool selected;
  MenuButtonType type;
} MenuOption;

typedef struct {
  MenuOption options[3];
  SDL_Texture* textures[3];
} Menu;

typedef struct {
  Joshim joshim;
  Map map;
  unsigned int time;
  unsigned int score;
  float scrollX;
  GameStatus status;
} Game;



#endif