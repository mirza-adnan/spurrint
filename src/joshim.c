#include "joshim.h"

void Joshim_Init(Joshim* joshim) {
  joshim->x = 20;
  joshim->y = 250;
  joshim->dx = 0;
  joshim->dy = 0;

  joshim->w = 64;
  joshim->h = 64;

  joshim->score = 0;

  joshim->lives = 9;

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

void Joshim_Draw(Game* game) {
  SDL_Rect dest = { game->joshim.x + game->scrollX, game->joshim.y, game->joshim.w, game->joshim.h };
  SDL_RenderCopyEx(Gfx_GetRenderer(), game->joshim.frames[game->joshim.currFrame], NULL, &dest, 0, NULL, game->joshim.facingRight);
}

void Joshim_Animate(Game* game) {
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
}

void Joshim_Move(Game* game) {
  game->joshim.x += game->joshim.dx;
  game->joshim.y += game->joshim.dy;

  if (game->joshim.applyGravity) {
    game->joshim.dy += GRAVITY;
  }
}

void Joshim_Update(Game* game) {
  Joshim_Animate(game);
  Joshim_Move(game);

  game->scrollX = -game->joshim.x + 320;

  if (game->scrollX > 0) {
    game->scrollX = 0;
  }
}

void Joshim_Cleanup(Joshim* joshim) {
  for (int i = 0; i < JOSHIM_TOTAL_FRAMES; i++) {
    SDL_DestroyTexture(joshim->frames[i]);
  }
}