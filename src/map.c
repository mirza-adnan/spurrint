#include "map.h"

void Map_Init(Map* map) {
  map->platformCount = 0;
  map->textures[BLOCK_TYPE_GRASS] = Gfx_LoadTexture("./src/assets/sprites/grass.png");
  map->textures[BLOCK_TYPE_BRICK] = Gfx_LoadTexture("./src/assets/sprites/brick.png");
  map->textures[BLOCK_TYPE_DIRT_1] = Gfx_LoadTexture("./src/assets/sprites/dirt_1.png");
  map->textures[BLOCK_TYPE_DIRT_2] = Gfx_LoadTexture("./src/assets/sprites/dirt_2.png");

  FILE* mapFile = fopen("./src/assets/maps/map1.dat", "rb");
  if (mapFile == NULL) {
    printf("Cannot find map file\n");
  }

  char line[1024];
  for (int i = 0; i < 15; i++) {
    fgets(line, 1023, mapFile);
    line[strcspn(line, "\n")] = 0;
    int size = 0;
    for (int j = 0; j < line[j + 1] != '\0'; j++) {
      BlockType block = line[j] - '0';
      int nextBlock = line[j + 1] - '0';
      if (block) {
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
        map->platformCount++;

        j += size - 1;  // -1 because j is gonna be incremented after this iteration
      }
    }
  }
  fclose(mapFile);
}

void Map_DrawPlatforms(Map* map) {
  for (int i = 0; i < map->platformCount; i++) {
    for (int j = 0; j < map->platforms[i].size; j++) {
      SDL_Rect dest = { map->platforms[i].x + (32 * j), map->platforms[i].y, 32, 32 };
      Gfx_BlitTexture(map->textures[map->platforms[i].type], &dest);
    }
  }
}

void Map_DetectCollision(Game* game) {
  if (game->joshim.currPlatform) {
    if ((game->joshim.x + game->joshim.w < game->joshim.currPlatform->x) ||
      (game->joshim.x > (game->joshim.currPlatform->x + game->joshim.currPlatform->w))) {
      game->joshim.applyGravity = true;
      game->joshim.onPlatform = false;
      game->joshim.continueJump = false;
    }
  }

  for (int i = 0; i < game->map.platformCount; i++) {
    float cW = game->joshim.w, cH = game->joshim.h;
    float cLeft = game->joshim.x, cTop = game->joshim.y;
    float cRight = cLeft + cW, cBottom = cTop + cH;

    float pW = game->map.platforms[i].w, pH = game->map.platforms[i].h;
    float pLeft = game->map.platforms[i].x, pTop = game->map.platforms[i].y;
    float pRight = pLeft + pW, pBottom = pTop + pH;

    if ((cLeft < pRight) && (cRight > pLeft) && (cTop < pBottom) && (cBottom > pTop)) {
      // colliding from the left
      if ((cRight > pLeft) && (cLeft < pLeft) && (cRight - pLeft < cBottom - pTop) && (cRight - pLeft < pBottom - cTop)) {
        game->joshim.dx = 0;
        game->joshim.x = pLeft - cW;
      }
      //landing on platform
      else if ((cBottom > pTop) && (cTop < pTop)) {
        game->joshim.dy = 0;
        game->joshim.y = pTop - cH;
        game->joshim.onPlatform = true;
        game->joshim.continueJump = false;
        game->joshim.applyGravity = false;
        game->joshim.currPlatform = &game->map.platforms[i];
      }
      // colliding from the right
      else if ((cLeft < pRight) & (cRight > pRight) && (pRight - cRight < cBottom - pTop) && (pRight - cLeft < pBottom - cTop)) {
        game->joshim.dx = 0;
        game->joshim.x = pRight;
      }
      // bumping head
      else if ((cTop < pBottom) && (cBottom > pBottom)) {
        game->joshim.dy = 0;
        game->joshim.y = pBottom;
      }
    }
  }
}

void Map_DrawMap(Map* map) {
  Map_DrawPlatforms(map);
}

void Map_Cleanup(Map* map) {
  for (int i = 0; i < BLOCK_TYPE_TOTAL; i++) {
    SDL_DestroyTexture(map->textures[i]);
  }
}