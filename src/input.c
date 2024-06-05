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
      case SDL_SCANCODE_SPACE:
        if (game->status = GAME_STATUS_GAME) {
          if (!event.key.repeat && game->joshim.onPlatform && !game->joshim.continueJump) {
            game->joshim.dy = -7;
            game->joshim.onPlatform = false;
            game->joshim.continueJump = true;
            game->joshim.applyGravity = true;
            game->joshim.hasJumped = true;
          }
        }
        break;
      case SDL_SCANCODE_R:
        if (game->status == GAME_STATUS_END) {
          Game_ResetAll(game);

          game->status = GAME_STATUS_GAME;
        }
        break;
      case SDL_SCANCODE_ESCAPE:
        if (game->status == GAME_STATUS_END) {
          Game_ResetAll(game);
          game->status = GAME_STATUS_MENU;
        }
        else if (game->status == GAME_STATUS_GAME) {
          game->status = GAME_STATUS_PAUSED;
        }
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (game->status == GAME_STATUS_MENU) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          MenuOption* options = Menu_GetOptions();
          int x, y;
          SDL_GetMouseState(&x, &y);
          for (int i = 0; i < MENU_BUTTON_TOTAL; i++) {
            if ((x > options[i].x) && (x < (options[i].x + options[i].w))) {
              if ((y > options[i].y) && (y < (options[i].y + options[i].h))) {
                if (options[i].type == MENU_BUTTON_PLAY) {
                  game->status = GAME_STATUS_GAME;
                  Game_ResetAll(game);
                }
                else if (options[i].type == MENU_BUTTON_EXIT) {
                  continueLoop = false;
                }
              }
            }
          }
        }
      }
      else if (game->status == GAME_STATUS_PAUSED) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          PauseOption* options = Menu_GetPauseOptions();
          int x, y;
          SDL_GetMouseState(&x, &y);
          for (int i = 0; i < PAUSE_BUTTON_TOTAL; i++) {
            if ((x > options[i].x) && (x < (options[i].x + options[i].w))) {
              if ((y > options[i].y) && (y < (options[i].y + options[i].h))) {
                if (options[i].type == PAUSE_BUTTON_RESTART) {
                  game->status = GAME_STATUS_GAME;
                  Game_ResetAll(game);
                }
                else if (options[i].type == PAUSE_BUTTON_EXIT) {
                  continueLoop = false;
                }
                else if (options[i].type == PAUSE_BUTTON_CONTINUE) {
                  game->status = GAME_STATUS_GAME;
                }
              }
            }
          }
        }
      }
      break;
    }
  }

  if (game->status == GAME_STATUS_GAME) {
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
  }

  return continueLoop;
}