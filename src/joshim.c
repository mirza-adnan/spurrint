#include "joshim.h"

void Joshim_Init(Joshim* joshim) {
  joshim->x = 50;
  joshim->y = 100;
  joshim->dx = 0;
  joshim->dy = 0;

  joshim->w = 64;
  joshim->h = 64;

  joshim->frames[JOSHIM_STAND_1] = Gfx_LoadTexture("./src/assets/sprites/joshim_stand_1.png");
  joshim->frames[JOSHIM_RUN_1] = Gfx_LoadTexture("./src/assets/sprites/joshim_run_1.png");
  joshim->frames[JOSHIM_RUN_2] = Gfx_LoadTexture("./src/assets/sprites/joshim_run_2.png");
  joshim->frameCount = 3;
  joshim->currFrame = JOSHIM_STAND_1;

  joshim->onPlatform = true;
  joshim->facingRight = true;
  joshim->slowingDown = false;
  joshim->hasJumped = false;
  joshim->continueJump = false;
}

void Joshim_Draw(Joshim* joshim) {
  SDL_Rect dest = { joshim->x, joshim->y, joshim->w, joshim->h };
  SDL_RenderCopyEx(Gfx_GetRenderer(), joshim->frames[joshim->currFrame], NULL, &dest, 0, NULL, joshim->facingRight);
}

void Joshim_Move(Game* game) {
  if (game->joshim.dx != 0 && !game->joshim.slowingDown) {
    if ((game->time % 6) == 0) {
      game->joshim.currFrame = (game->joshim.currFrame + 1) % JOSHIM_TOTAL;
    }
  }
  else {
    game->joshim.currFrame = JOSHIM_STAND_1;
  }

  game->joshim.x += game->joshim.dx;
  game->joshim.y += game->joshim.dy;
}

void Joshim_Cleanup(Joshim* joshim) {
  for (int i = 0; i < joshim->frameCount; i++) {
    SDL_DestroyTexture(joshim->frames[i]);
  }
}