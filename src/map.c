#include "map.h"

#define ENDING_X 7515

void Map_Init(Map* map) {
  map->platformCount = 0;
  map->collectibleCount = 0;
  map->textures[BLOCK_TYPE_GRASS] = Gfx_LoadTexture("./src/assets/sprites/grass.png");
  map->textures[BLOCK_TYPE_BRICK] = Gfx_LoadTexture("./src/assets/sprites/brick.png");
  map->textures[BLOCK_TYPE_DIRT_1] = Gfx_LoadTexture("./src/assets/sprites/dirt_1.png");
  map->textures[BLOCK_TYPE_DIRT_2] = Gfx_LoadTexture("./src/assets/sprites/dirt_2.png");
  map->textures[BLOCK_TYPE_CHICKEN] = Gfx_LoadTexture("./src/assets/sprites/drumstick.png");

  map->chickenTex[0] = Gfx_LoadTexture("./src/assets/sprites/drumstick.png");
  map->chickenTex[1] = Gfx_LoadTexture("./src/assets/sprites/drumstick2.png");
  map->chickenTex[2] = Gfx_LoadTexture("./src/assets/sprites/drumstick3.png");
  map->chickenTex[3] = Gfx_LoadTexture("./src/assets/sprites/drumstick4.png");
  map->chickenTex[4] = Gfx_LoadTexture("./src/assets/sprites/drumstick5.png");
  map->chickenTex[5] = Gfx_LoadTexture("./src/assets/sprites/drumstick6.png");

  map->manTex[0] = Gfx_LoadTexture("./src/assets/sprites/man.png");
  map->manTex[1] = Gfx_LoadTexture("./src/assets/sprites/man_walk_1.png");
  map->manTex[2] = Gfx_LoadTexture("./src/assets/sprites/man_walk_2.png");

  map->fcatTex[0] = Gfx_LoadTexture("./src/assets/sprites/fcat1.png");
  map->fcatTex[1] = Gfx_LoadTexture("./src/assets/sprites/fcat2.png");
  map->fcatTex[2] = Gfx_LoadTexture("./src/assets/sprites/fcat3.png");

  map->endTex[0] = Gfx_LoadTexture("./src/assets/sprites/ending1.png");
  map->endTex[1] = Gfx_LoadTexture("./src/assets/sprites/ending2.png");
  map->endTex[2] = Gfx_LoadTexture("./src/assets/sprites/ending3.png");
  map->endTex[3] = Gfx_LoadTexture("./src/assets/sprites/ending4.png");

  map->endFrame = 0;

  map->fcatFrame = 0;

  map->manFrame = 0;

  map->heart = Gfx_LoadTexture("./src/assets/sprites/heart1.png");

  map->buildings[0] = Gfx_LoadTexture("./src/assets/buildings/building1.png");
  map->buildings[1] = Gfx_LoadTexture("./src/assets/buildings/building2.png");
  map->buildings[2] = Gfx_LoadTexture("./src/assets/buildings/building3.png");
  map->buildings[3] = Gfx_LoadTexture("./src/assets/buildings/building4.png");
  map->buildings[4] = Gfx_LoadTexture("./src/assets/buildings/building5.png");
  map->buildings[5] = Gfx_LoadTexture("./src/assets/buildings/building6.png");
  map->buildings[6] = Gfx_LoadTexture("./src/assets/buildings/pillars.png");

  map->humanCount = 0;

  FILE* mapFile = fopen("./src/assets/maps/map1.dat", "rb");
  if (mapFile == NULL) {
    printf("Cannot find map file\n");
  }

  char line[1024];
  for (int i = 0; i < 15; i++) {
    fgets(line, 1023, mapFile);
    line[strcspn(line, "\n")] = 0;
    Util_RemoveSpaces(line);
    int size = 0;
    for (int j = 0; line[j + 1] != '\0'; j++) {
      BlockType block = line[j] - '0';
      // int nextBlock = line[j + 1] - '0';
      if (block) {
        if (block == BLOCK_TYPE_CHICKEN) {
          map->collectibles[map->collectibleCount].x = 32 * j;
          map->collectibles[map->collectibleCount].y = 32 * i;
          map->collectibles[map->collectibleCount].w = 32;
          map->collectibles[map->collectibleCount].h = 32;
          map->collectibles[map->collectibleCount].collected = false;
          map->collectibleCount++;
        }
        else if (block == BLOCK_TYPE_HUMAN) {
          map->humans[map->humanCount].x = 32 * j;
          map->humans[map->humanCount].y = 32 * i;
          map->humans[map->humanCount].active = true;
          map->humans[map->humanCount].maxRight = map->humans[map->humanCount].x + (32 * 2);
          map->humans[map->humanCount].maxLeft = map->humans[map->humanCount].x - (32 * 2);
          map->humans[map->humanCount].faceLeft = false;
          map->humans[map->humanCount].dx = 1;
          map->humanCount++;
        }
        else {
          int size = 0;
          for (int k = j; line[k] - '0' == block && line[k] != '\0'; k++) {
            size++;
          }

          map->platforms[map->platformCount].x = 32 * j;
          map->platforms[map->platformCount].y = 32 * i;
          map->platforms[map->platformCount].w = 32 * size;
          map->platforms[map->platformCount].h = 32;
          map->platforms[map->platformCount].size = size;
          map->platforms[map->platformCount].type = block;
          map->platforms[map->platformCount].touched = false;
          map->platformCount++;

          j += size - 1;  // -1 because j is gonna be incremented after this iteration
        }

      }
    }
  }
  fclose(mapFile);
}

void Map_DrawPlatforms(Game* game) {
  for (int i = 0; i < game->map.platformCount; i++) {
    for (int j = 0; j < game->map.platforms[i].size; j++) {
      SDL_Rect dest = { game->map.platforms[i].x + (32 * j) + game->scrollX, game->map.platforms[i].y, 32, 32 };
      Gfx_BlitTexture(game->map.textures[game->map.platforms[i].type], &dest);
    }
  }
}

void Map_DrawCollectibles(Game* game) {
  for (int i = 0; i < game->map.collectibleCount; i++) {
    if (!game->map.collectibles[i].collected) {
      SDL_Rect dest = { game->map.collectibles[i].x + game->scrollX, game->map.collectibles[i].y, game->map.collectibles[i].w, game->map.collectibles[i].h };
      Gfx_BlitTexture(game->map.chickenTex[game->map.chickenFrame], &dest);
    }
  }
  if (game->time % 8 == 0) {
    game->map.chickenFrame = (game->map.chickenFrame + 1) % 6;
  }
}

void Map_CollectCollectible(Game* game) {
  for (int i = 0; i < game->map.collectibleCount; i++) {
    float cW = game->joshim.w, cH = game->joshim.h;
    float cLeft = game->joshim.x, cTop = game->joshim.y;
    float cRight = cLeft + cW, cBottom = cTop + cH;

    float dW = game->map.collectibles[i].w, dH = game->map.collectibles[i].h;
    float dLeft = game->map.collectibles[i].x, dTop = game->map.collectibles[i].y;
    float dRight = dLeft + dW, dBottom = dTop + dH;

    if (!game->map.collectibles[i].collected) {
      if ((cTop < dBottom) && (cBottom > dTop) && (cRight > dLeft) && (cLeft < dRight)) {
        game->map.collectibles[i].collected = true;
        game->score += 10;
        Music_Collect();
      }

    }
  }
}

void Map_CheckIfLeftPlatform(Joshim* joshim) {
  // checking if player left the last platform they were on
  if (joshim->currPlatform) {
    if ((joshim->x + joshim->w < joshim->currPlatform->x) ||
      (joshim->x > (joshim->currPlatform->x + joshim->currPlatform->w))) {
      joshim->applyGravity = true;
      joshim->onPlatform = false;
      joshim->continueJump = false;
    }
  }
}

void Map_DetectCollision(Game* game, int i) {
  float cW = game->joshim.w, cH = game->joshim.h;
  float cLeft = game->joshim.x, cTop = game->joshim.y;
  float cRight = cLeft + cW, cBottom = cTop + cH;

  float pW = game->map.platforms[i].w, pH = game->map.platforms[i].h;
  float pLeft = game->map.platforms[i].x, pTop = game->map.platforms[i].y;
  float pRight = pLeft + pW, pBottom = pTop + pH;

  if ((cLeft < pRight) && (cRight > pLeft) && (cTop < pBottom) && (cBottom > pTop)) {
    /*!!!THE ORDER OF IF STATEMENTS IS IMPORTANT!!!*/
    // colliding from the left
    if ((cRight > pLeft) && (cLeft < pLeft) && (cRight - pLeft < cBottom - pTop) && (cRight - pLeft < pBottom - cTop)) {
      game->joshim.dx = 0;
      game->joshim.x = pLeft - cW;
    }
    // colliding from the right
    else if ((cLeft < pRight) & (cRight > pRight) && (pRight - cLeft < cBottom - pTop) && (pRight - cLeft < pBottom - cTop)) {
      game->joshim.dx = 0;
      game->joshim.x = pRight;
    }
    //landing on platform
    else if ((cBottom > pTop) && (cTop < pTop)) {
      game->joshim.dy = 0;
      game->joshim.y = pTop - cH;
      game->joshim.onPlatform = true;
      game->joshim.continueJump = false;
      game->joshim.hasJumped = false;
      game->joshim.applyGravity = false;
      game->joshim.currPlatform = &game->map.platforms[i];

      if (game->map.platforms[i].type != 1 && !game->map.platforms[i].touched) {
        game->score += 5;
        game->map.platforms[i].touched = true;
      }
    }
    // bumping head
    else if ((cTop < pBottom) && (cBottom > pBottom)) {
      game->joshim.dy = 0;
      game->joshim.y = pBottom;
      game->joshim.continueJump = false;
      game->joshim.hasJumped = false;
    }
  }
}

void Map_HandleDeath(Game* game) {
  game->joshim.lives--;
  game->time = 0;
  game->joshim.x = 20;
  game->joshim.y = 250;
  game->joshim.dx = 0;
  game->joshim.dy = 0;
  game->scrollX = 0;
}

void Map_KeepInBounds(Game* game) {
  if (game->joshim.x < 0) {
    game->joshim.x = 0;
  }
  if (game->joshim.x > 7898) {
    game->joshim.x = 7898;
  }
}

void Map_Update(Game* game) {
  Map_CheckIfLeftPlatform(&game->joshim);
  Map_KeepInBounds(game);

  for (int i = 0; i < game->map.platformCount; i++) {
    Map_DetectCollision(game, i);
  }
}

void Map_DrawSky(Game* game) {
  SDL_SetRenderDrawColor(Gfx_GetRenderer(), 135, 206, 235, 255);
  SDL_RenderClear(Gfx_GetRenderer());
}

void Map_DrawBuildings(Game* game) {
  SDL_Rect rect = { 20 + game->scrollX, 100, 0, 0 };

  SDL_QueryTexture(game->map.buildings[0], NULL, NULL, &rect.w, &rect.h);
  Gfx_BlitTexture(game->map.buildings[0], &rect);

  SDL_QueryTexture(game->map.buildings[4], NULL, NULL, &rect.w, &rect.h);
  rect.x = 1440 + game->scrollX;
  rect.y = SCREEN_HEIGHT - 128 - rect.h;
  Gfx_BlitTexture(game->map.buildings[4], &rect);

  SDL_QueryTexture(game->map.buildings[1], NULL, NULL, &rect.w, &rect.h);
  rect.x = 3040 + game->scrollX;
  rect.y = SCREEN_HEIGHT - 128 - rect.h + 2;
  Gfx_BlitTexture(game->map.buildings[1], &rect);

  rect.x = 3040 + game->scrollX + rect.w + 30;
  SDL_QueryTexture(game->map.buildings[2], NULL, NULL, &rect.w, &rect.h);
  rect.y = SCREEN_HEIGHT - 128 - rect.h;
  Gfx_BlitTexture(game->map.buildings[2], &rect);

  SDL_QueryTexture(game->map.buildings[5], NULL, NULL, &rect.w, &rect.h);
  rect.x = 6560 + game->scrollX;
  rect.y = SCREEN_HEIGHT - 128 - rect.h + 2;
  Gfx_BlitTexture(game->map.buildings[5], &rect);

  SDL_QueryTexture(game->map.buildings[6], NULL, NULL, &rect.w, &rect.h);
  rect.x = 7350 + game->scrollX;
  rect.y = SCREEN_HEIGHT - 128 - rect.h;
  Gfx_BlitTexture(game->map.buildings[6], &rect);
}

void Map_DrawScore(Game* game) {
  char str[6];
  sprintf(str, "%d", game->score);

  SDL_Color black = { 0, 0, 0, 255 };
  Text_DrawText(false, 560, 5, str, black, FONT_SIZE_48_BOLD);
}

void Map_DrawLives(Game* game) {
  char str[3];
  sprintf(str, "%dx", game->joshim.lives);

  SDL_Color black = { 0, 0, 0, 255 };
  Text_DrawText(false, 16, 2, str, black, FONT_SIZE_42);

  SDL_Rect heartRect;
  SDL_QueryTexture(game->map.heart, NULL, NULL, &heartRect.w, &heartRect.h);
  heartRect.w *= 1;
  heartRect.h *= 1;
  heartRect.x = 60;
  heartRect.y = 20;
  Gfx_BlitTexture(game->map.heart, &heartRect);
}

void Map_DrawHumans(Game* game) {
  for (int i = 0; i < game->map.humanCount; i++) {
    Human* human = &game->map.humans[i];
    SDL_Rect manRect = { (int)human->x + (int)game->scrollX, (int)human->y, 0, 0 };
    SDL_QueryTexture(game->map.manTex[game->map.manFrame], NULL, NULL, &manRect.w, &manRect.h);

    //printf("%d %f %f\n", manRect.x, human->maxRight, human->dx);

    manRect.w *= 3.5;
    manRect.h *= 3.5;

    human->w = manRect.w;
    human->h = manRect.h;

    manRect.y = human->y + 32 - manRect.h;

    if (!human->faceLeft) {
      if (human->x > human->maxRight) {
        human->faceLeft = true;
        human->dx = -(human->dx);
      }
    }
    else {
      if (human->x < human->maxLeft) {
        human->faceLeft = false;
        human->dx = -(human->dx);
      }
    }
    human->x += human->dx;

    Gfx_ExBlitTexture(game->map.manTex[game->map.manFrame], &manRect, human->faceLeft);
  }
  if (game->time % 15 == 0) {
    game->map.manFrame = (game->map.manFrame + 1) % 3;
  }
}

void Map_HandleHumanHit(Game* game) {
  Joshim* joshim = &game->joshim;

  for (int i = 0; i < game->map.humanCount; i++) {
    Human* human = &game->map.humans[i];
    float cW = game->joshim.w, cH = game->joshim.h;
    float cLeft = game->joshim.x, cTop = game->joshim.y;
    float cRight = cLeft + cW, cBottom = cTop + cH;

    float dW = human->w, dH = human->h;
    float dLeft = human->x, dTop = human->y + 32 - human->h;
    float dRight = dLeft + dW, dBottom = dTop + dH;

    if ((cTop < dBottom) && (cBottom > dTop) && (cRight > dLeft) && (cLeft < dRight)) {
      Music_Damage();
      Game_HandleDeath(game);
    }
  }
}

void Map_DrawFcat(Game* game) {
  if (game->status == GAME_STATUS_GAME) {
    SDL_Rect fcatRect = { ENDING_X + game->scrollX, SCREEN_HEIGHT - 128 - 48, 48, 48 };
    Gfx_BlitTexture(game->map.fcatTex[game->map.fcatFrame], &fcatRect);

    if (game->time % 20 == 0) {
      game->map.fcatFrame = (game->map.fcatFrame + 1) % 3;
    }
  }
}

void Map_TriggerEnding(Game* game) {
  Joshim* joshim = &game->joshim;
  if (game->status == GAME_STATUS_GAME) {
    if ((joshim->y < (SCREEN_HEIGHT - 128)) && ((joshim->y + joshim->h) > (SCREEN_HEIGHT - 128 - 64))) {
      if ((joshim->x + joshim->w) > ENDING_X && (joshim->x < (ENDING_X + 64))) {
        game->status = GAME_STATUS_ENDING;
        game->endTime = game->time;
      }
    }
  }
}

void Map_EndingAnimation(Game* game) {
  SDL_Rect rect = { ENDING_X - 64 + game->scrollX, SCREEN_HEIGHT - 128 - 104 + 32, 0, 0 };
  SDL_QueryTexture(game->map.endTex[0], NULL, NULL, &rect.w, &rect.h);
  rect.w *= 0.7;
  rect.h *= 0.7;
  Gfx_BlitTexture(game->map.endTex[game->map.endFrame], &rect);

  if (game->time % 20 == 0) {
    game->map.endFrame = (game->map.endFrame + 1) % 4;
  }
  if (game->time == (game->endTime + 300)) {
    game->status = GAME_STATUS_MENU;
  }
}

void Map_DrawMap(Game* game) {
  Map_DrawSky(game);
  Map_DrawBuildings(game);
  Map_DrawPlatforms(game);
  Map_DrawCollectibles(game);
  Map_DrawHumans(game);
  Map_DrawScore(game);
  Map_DrawLives(game);

  if (game->status == GAME_STATUS_GAME) {
    Map_HandleHumanHit(game);
    Map_DrawFcat(game);
    Map_TriggerEnding(game);
  }
}

void Map_Cleanup(Map* map) {
  for (int i = 0; i < BLOCK_TYPE_TOTAL; i++) {
    SDL_DestroyTexture(map->textures[i]);
  }

  for (int i = 0; i < 7; i++) {
    SDL_DestroyTexture(map->buildings[i]);
  }
  SDL_DestroyTexture(map->heart);

  for (int i = 0; i < 3; i++) {
    SDL_DestroyTexture(map->manTex[i]);
  }

  for (int i = 0; i < 3; i++) {
    SDL_DestroyTexture(map->fcatTex[i]);
  }

  for (int i = 0; i < 4; i++) {
    SDL_DestroyTexture(map->endTex[i]);
  }

  for (int i = 0; i < 6; i++) {
    SDL_DestroyTexture(map->chickenTex[i]);
  }
}