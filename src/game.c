#include "game.h"

Game game;

void Game_Start() {
  SDL_Init(SDL_INIT_EVERYTHING);
  Gfx_Init();
  TTF_Init();
  Game_Init();
  Text_Init();
  Map_Init(&game.map);
  Joshim_Init(&game.joshim);
  Game_GameLoop();
}

void Game_Init() {
  game.score = 0;
  game.time = 0;
  game.scrollX = 0;
}

void Game_RenderCycle() {
  Gfx_ClearRend();
  Map_DrawMap(&game);
  Joshim_Move(&game);
  Map_CollectCollectible(&game);
  Map_DetectCollision(&game);
  Joshim_Draw(&game);
  Text_DrawScore(&game);
  Gfx_PresentRend();
}

void Game_GameLoop() {
  SDL_Event event;
  while (Inp_EventLoop(&game)) {
    game.time++;
    Game_RenderCycle();
    SDL_Delay(16);
  }
}

void Game_Cleanup() {
  Gfx_Cleanup();
  Joshim_Cleanup(&game.joshim);
  Map_Cleanup(&game.map);

  TTF_Quit();
  SDL_Quit();
}