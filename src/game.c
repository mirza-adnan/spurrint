#include "game.h"

Game game;

void Game_Start() {
  SDL_Init(SDL_INIT_EVERYTHING);
  Gfx_Init();
  TTF_Init();
  Game_Init();
  Text_Init();
  Menu_Init();
  Map_Init(&game.map);
  Joshim_Init(&game.joshim);
  Game_GameLoop();
}

void Game_Init() {
  game.score = 0;
  game.status = GAME_STATUS_MENU;
  game.time = 0;
  game.scrollX = 0;
}

void Game_RenderGame() {
  Map_DrawMap(&game);
  Joshim_Move(&game);
  Map_CollectCollectible(&game);
  Map_DetectCollision(&game);
  Joshim_Draw(&game);
  Text_DrawScore(&game);
}

void Game_RenderEnd() {
  SDL_SetRenderDrawColor(Gfx_GetRenderer(), 0, 0, 0, 255);
  Gfx_ClearRend();
  SDL_Color color = { 249, 112, 90, 255 };
  Text_DrawText(true, -1, SCREEN_HEIGHT / 2 - 80, "Game Over", color, FONT_SIZE_48);
  SDL_Color white = { 255, 255, 255, 255 };
  Text_DrawText(true, -1, SCREEN_HEIGHT / 2 - 40, "Press R to try again", white, FONT_SIZE_36);
}

void Game_RenderCycle() {
  Gfx_ClearRend();

  if (game.status == GAME_STATUS_MENU) {
    Menu_DrawMenu();
  }
  else if (game.status == GAME_STATUS_GAME) {
    Game_RenderGame();
  }
  else if (game.status == GAME_STATUS_END) {
    Game_RenderEnd();
  }

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
  Menu_Cleanup();

  TTF_Quit();
  SDL_Quit();
}