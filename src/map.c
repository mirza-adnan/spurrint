#include "map.h"

void Map_Init(Map* map) {
  map->platformCount = 0;
  map->collectibleCount = 0;
  map->textures[BLOCK_TYPE_GRASS] = Gfx_LoadTexture("./src/assets/sprites/grass.png");
  map->textures[BLOCK_TYPE_BRICK] = Gfx_LoadTexture("./src/assets/sprites/brick.png");
  map->textures[BLOCK_TYPE_DIRT_1] = Gfx_LoadTexture("./src/assets/sprites/dirt_1.png");
  map->textures[BLOCK_TYPE_DIRT_2] = Gfx_LoadTexture("./src/assets/sprites/dirt_2.png");
  map->textures[BLOCK_TYPE_CHICKEN] = Gfx_LoadTexture("./src/assets/sprites/drumstick.png");

  map->buildings[0] = Gfx_LoadTexture("./src/assets/buildings/building1.png");

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
      Gfx_BlitTexture(game->map.textures[BLOCK_TYPE_CHICKEN], &dest);
    }
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
      }

    }
  }
}

void Map_DetectCollision(Game* game) {
  // checking if player left the last platform they were on
  if (game->joshim.currPlatform) {
    if ((game->joshim.x + game->joshim.w < game->joshim.currPlatform->x) ||
      (game->joshim.x > (game->joshim.currPlatform->x + game->joshim.currPlatform->w))) {
      game->joshim.applyGravity = true;
      game->joshim.onPlatform = false;
      game->joshim.continueJump = false;
    }
  }

  if (game->joshim.x < 0) {
    game->joshim.x = 0;
  }
  if (game->joshim.y + game->joshim.h > SCREEN_HEIGHT) {
    game->status = GAME_STATUS_END;
  }

  for (int i = 0; i < game->map.platformCount; i++) {
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
}

void Map_DrawSky(Game* game) {
  SDL_SetRenderDrawColor(Gfx_GetRenderer(), 135, 206, 235, 255);
  SDL_RenderClear(Gfx_GetRenderer());
}

void Map_DrawBuildings(Game* game) {
  SDL_Rect rect1 = { 20 + game->scrollX, 100, 0, 0 };
  SDL_QueryTexture(game->map.buildings[0], NULL, NULL, &rect1.w, &rect1.h);
  Gfx_BlitTexture(game->map.buildings[0], &rect1);
}

void Map_DrawMap(Game* game) {
  Map_DrawSky(game);
  Map_DrawBuildings(game);
  Map_DrawPlatforms(game);
  Map_DrawCollectibles(game);
}

void Map_Cleanup(Map* map) {
  for (int i = 0; i < BLOCK_TYPE_TOTAL; i++) {
    SDL_DestroyTexture(map->textures[i]);
  }

  for (int i = 0; i < 2; i++) {
    SDL_DestroyTexture(map->buildings[i]);
  }
}