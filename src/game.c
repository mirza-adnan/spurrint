#include "game.h"

Game game;

void Game_Init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  gfx_Init();
  Game_GameLoop();
  printf("hello\n");
}

void Game_GameLoop() {
  SDL_Event event;
  while (1) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
}