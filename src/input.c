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
      case SDL_SCANCODE_R:
        if (game->status == GAME_STATUS_END) {
          game->time = 0;
          game->joshim.x = 20;
          game->joshim.y = 250;
          game->joshim.dx = 0;
          game->joshim.dy = 0;
          game->scrollX = 0;
          game->score = 0;

          for (int i = 0; i < game->map.platformCount; i++) {
            game->map.platforms[i].touched = false;
          }
          for (int i = 0; i < game->map.collectibleCount; i++) {
            game->map.collectibles[i].collected = false;
          }

          game->status = GAME_STATUS_GAME;
        }
      }
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT) {
        MenuOption* options = Menu_GetOptions();
        int x, y;
        SDL_GetMouseState(&x, &y);
        for (int i = 0; i < MENU_BUTTON_TOTAL; i++) {
          if ((x > options[i].x) && (x < (options[i].x + options[i].w))) {
            if ((y > options[i].y) && (y < (options[i].y + options[i].h))) {
              if (options[i].type == MENU_BUTTON_PLAY) {
                game->status = GAME_STATUS_GAME;
              }
              else if (options[i].type == MENU_BUTTON_EXIT) {
                continueLoop = false;
              }
            }
          }
        }
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