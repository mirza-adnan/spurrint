#include "game.h"

Game game;

void Game_Start() {
  SDL_Init(SDL_INIT_EVERYTHING);
  Gfx_Init();
  Game_Init();
  Game_GameLoop();
}

void Game_Init() {
  game.time = 0;
  Joshim_Init(&game.joshim);
}

void Game_RenderCycle() {
  Gfx_ClearRend();
  Joshim_Move(&game);
  Joshim_Draw(&game.joshim);
  Gfx_PresentRend();
}

void Game_GameLoop() {
  SDL_Event event;
  while (Inp_Process(&game)) {
    game.time++;
    Game_RenderCycle();
  }
}

void Game_Cleanup() {
  Gfx_Cleanup();
  Joshim_Cleanup(&game.joshim);
}