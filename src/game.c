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
  Music_Init();
  Joshim_Init(&game.joshim);
  Game_GameLoop();
}

void Game_Init() {
  game.score = 0;
  game.status = GAME_STATUS_MENU;
  game.time = 0;
  game.scrollX = 0;
  game.endTime = 0;
}

void Game_ResetAll(Game* game) {
  game->joshim.lives--;
  game->time = 0;
  game->joshim.x = 20;
  game->joshim.y = 250;
  game->joshim.dx = 0;
  game->joshim.dy = 0;
  game->scrollX = 0;
  game->joshim.lives = 3;
  game->joshim.score = 0;
  game->score = 0;
  game->endTime = 0;

  game->joshim.onPlatform = false;
  game->joshim.facingRight = true;
  game->joshim.slowingDown = false;
  game->joshim.hasJumped = false;
  game->joshim.continueJump = false;
  game->joshim.applyGravity = true;

  for (int i = 0; i < game->map.platformCount; i++) {
    game->map.platforms[i].touched = false;
  }
  for (int i = 0; i < game->map.collectibleCount; i++) {
    game->map.collectibles[i].collected = false;
  }
}

void Game_HandleDeath(Game* game) {
  game->joshim.lives--;
  game->time = 0;
  game->joshim.x = 20;
  game->joshim.y = 250;
  game->joshim.dx = 0;
  game->joshim.dy = 0;

  game->joshim.onPlatform = false;
  game->joshim.facingRight = true;
  game->joshim.slowingDown = false;
  game->joshim.hasJumped = false;
  game->joshim.continueJump = false;
  game->joshim.applyGravity = true;
}

void Game_HandleEnd(Game* game) {
  if (game->joshim.lives == 0) {
    game->status = GAME_STATUS_END;
    Music_Stop();
  }
  else {
    if (game->joshim.y + game->joshim.h > SCREEN_HEIGHT) {
      Music_Damage();
      Game_HandleDeath(game);
    }
  }
}

void Game_RenderGame() {
  Map_DrawMap(&game);
  if (game.status == GAME_STATUS_GAME) {
    Joshim_Update(&game);
    Joshim_Draw(&game);
  }
  else if (game.status == GAME_STATUS_ENDING) {
    Map_EndingAnimation(&game);
  }
  Map_CollectCollectible(&game);
  Map_Update(&game);
  Game_HandleEnd(&game);
}

void Game_RenderEnding() {
  Map_DrawMap(&game);
  Map_EndingAnimation(&game);
  Map_CollectCollectible(&game);
}

void Game_RenderEnd() {
  SDL_SetRenderDrawColor(Gfx_GetRenderer(), 0, 0, 0, 255);
  Gfx_ClearRend();
  SDL_Color color = { 249, 112, 90, 255 };
  Text_DrawText(true, -1, SCREEN_HEIGHT / 2 - 80, "Game Over", color, FONT_SIZE_48);
  SDL_Color white = { 255, 255, 255, 255 };
  Text_DrawText(true, -1, SCREEN_HEIGHT / 2 - 40, "Press R to try again", white, FONT_SIZE_36);
  Text_DrawText(true, -1, SCREEN_HEIGHT / 2 - 15, "Or press Esc to return to Main Menu", white, FONT_SIZE_36);
}

void Game_RenderCycle() {
  Gfx_ClearRend();

  if (game.status == GAME_STATUS_MENU) {
    if (!Music_IsPlaying()) {
      Music_Play();
    }
    Menu_DrawMenu();
  }
  else if (game.status == GAME_STATUS_PAUSED) {
    if (!Music_IsPlaying()) {
      Music_Play();
    }
    Menu_DrawPauseMenu();
  }
  else if (game.status == GAME_STATUS_GAME || game.status == GAME_STATUS_ENDING) {
    if (!Music_IsPlaying()) {
      Music_Play();
    }
    Game_RenderGame();
  }
  else if (game.status == GAME_STATUS_END) {
    if (Music_IsPlaying()) {
      Music_Stop();
    }
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
  Music_Cleanup();

  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}