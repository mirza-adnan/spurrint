#include "input.h"

bool Inp_EventLoop(Game* game) {
  bool continueLoop = true;

  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      continueLoop = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_ESCAPE:
        continueLoop = false;
        break;
      case SDL_SCANCODE_SPACE:
        if (!event.key.repeat && game->joshim.onPlatform && !game->joshim.continueJump) {
          game->joshim.dy = -7;
          game->joshim.onPlatform = false;
          game->joshim.continueJump = true;
          game->joshim.applyGravity = true;
          game->joshim.hasJumped = true;
        }
        break;
      }
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
    game->joshim.dx -= 0.5;
    game->joshim.facingRight = false;
    game->joshim.slowingDown = false;
    if (game->joshim.dx < -MAX_SPEED) {
      game->joshim.dx = -MAX_SPEED;
    }
  }
  else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
    game->joshim.dx += 0.5;
    game->joshim.facingRight = true;
    game->joshim.slowingDown = false;
    if (game->joshim.dx > MAX_SPEED) {
      game->joshim.dx = MAX_SPEED;
    }
  }

  if (!(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) && !(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])) {
    game->joshim.dx *= 0.8f;
    game->joshim.slowingDown = true;
    if (SDL_fabsf(game->joshim.dx) < 0.1f) {
      game->joshim.dx = 0;
    }
  }

  if (state[SDL_SCANCODE_SPACE]) {
    if (game->joshim.hasJumped && !game->joshim.onPlatform) {
      game->joshim.dy -= 0.28f;
    }
  }

  if (!state[SDL_SCANCODE_SPACE]) {
    game->joshim.continueJump = false;
  }


  return continueLoop;
}