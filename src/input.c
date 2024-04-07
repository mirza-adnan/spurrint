#include "input.h"

bool Inp_Process(Game* game) {
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
        break;
      }
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
    game->joshim.dx -= 0.5;
    game->joshim.facingRight = false;
    game->joshim.slowingDown = false;
    if (game->joshim.dx < -6) {
      game->joshim.dx = -6;
    }
  }

  if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
    game->joshim.dx += 0.5;
    game->joshim.facingRight = true;
    game->joshim.slowingDown = false;
    if (game->joshim.dx > 6) {
      game->joshim.dx = 6;
    }
  }

  if (!(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) && !(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])) {
    game->joshim.dx *= 0.8f;
    game->joshim.slowingDown = true;
    if (SDL_fabsf(game->joshim.dx) < 0.1f) {
      game->joshim.dx = 0;
    }
  }
  return continueLoop;
}