#include "joshim.h"

void Joshim_Init(Joshim* joshim) {
  joshim->x = 50;
  joshim->y = 100;
  joshim->dx = 0;
  joshim->dy = 0;

  joshim->w = 64;
  joshim->h = 64;

  joshim->frames[JOSHIM_RUN_1] = Gfx_LoadTexture("./src/assets/sprites/joshim_stand_1.png");
  joshim->frames[JOSHIM_RUN_2] = Gfx_LoadTexture("./src/assets/sprites/joshim_run_1.png");
  joshim->frames[JOSHIM_RUN_3] = Gfx_LoadTexture("./src/assets/sprites/joshim_run_2.png");
  joshim->frames[JOSHIM_IDLE_1] = Gfx_LoadTexture("./src/assets/sprites/joshim_idle_1.png");
  joshim->frames[JOSHIM_IDLE_2] = Gfx_LoadTexture("./src/assets/sprites/joshim_idle_2.png");
  joshim->frames[JOSHIM_IDLE_3] = Gfx_LoadTexture("./src/assets/sprites/joshim_idle_3.png");
  joshim->frames[JOSHIM_JUMP_1] = Gfx_LoadTexture("./src/assets/sprites/joshim_jump_1.png");

  joshim->currFrame = JOSHIM_IDLE_1;

  joshim->currPlatform = NULL;

  joshim->onPlatform = false;
  joshim->facingRight = true;
  joshim->slowingDown = false;
  joshim->hasJumped = false;
  joshim->continueJump = false;
  joshim->applyGravity = true;
}

void Joshim_Draw(Joshim* joshim) {
  SDL_Rect dest = { joshim->x, joshim->y, joshim->w, joshim->h };
  SDL_RenderCopyEx(Gfx_GetRenderer(), joshim->frames[joshim->currFrame], NULL, &dest, 0, NULL, joshim->facingRight);
}

void Joshim_Move(Game* game) {
  if (!game->joshim.onPlatform) {
    game->joshim.currFrame = JOSHIM_JUMP_1;
  }
  else if (game->joshim.dx == 0 && game->joshim.dy == 0) {
    if ((game->time % 20) == 0) {
      game->joshim.currFrame = ((game->joshim.currFrame + 1) % 3) + 3;
    }
  }
  else if (game->joshim.dx != 0 && !game->joshim.slowingDown) {
    if ((game->time % FRAMES_PER_ANIM) == 0) {
      game->joshim.currFrame = (game->joshim.currFrame + 1) % 3;
    }
  }
  else {
    game->joshim.currFrame = JOSHIM_IDLE_1;
  }

  game->joshim.x += game->joshim.dx;
  game->joshim.y += game->joshim.dy;

  if (game->joshim.applyGravity) {
    game->joshim.dy += GRAVITY;
  }

  if (game->joshim.y + game->joshim.h > SCREEN_HEIGHT) {
    game->joshim.y = SCREEN_HEIGHT - game->joshim.h;
  }
}

void Joshim_Cleanup(Joshim* joshim) {
  for (int i = 0; i < JOSHIM_TOTAL_FRAMES; i++) {
    SDL_DestroyTexture(joshim->frames[i]);
  }
}