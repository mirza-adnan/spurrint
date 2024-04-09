#include "game.h"

Game game;

void Game_Start() {
  SDL_Init(SDL_INIT_EVERYTHING);
  Gfx_Init();
  Map_Init(&game.map);
  Game_Init();
  Game_GameLoop();
}

void Game_Init() {
  game.time = 0;
  Joshim_Init(&game.joshim);
}

void Game_RenderCycle() {
  Gfx_ClearRend();
  Map_DrawMap(&game.map);
  Joshim_Move(&game);
  Map_DetectCollision(&game);
  Joshim_Draw(&game.joshim);
  Gfx_PresentRend();
}

void Game_GameLoop() {
  SDL_Event event;
  while (Inp_EventLoop(&game)) {
    game.time++;
    Game_RenderCycle();
  }
}

void Game_Cleanup() {
  Gfx_Cleanup();
  Joshim_Cleanup(&game.joshim);
  Map_Cleanup(&game.map);
}