#include "map.h"

Map map;

void Map_Init() {
  map.platformCount = 0;
  map.grassTexture = Gfx_LoadTexture("./src/assets/sprites/grass.png");
  map.brickTexture = Gfx_LoadTexture("./src/assets/sprites/brick.png");

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

        map.platforms[map.platformCount].x = 32 * j;
        map.platforms[map.platformCount].y = 32 * i;
        map.platforms[map.platformCount].w = 32 * size;
        map.platforms[map.platformCount].h = 32;
        map.platforms[map.platformCount].size = size;
        map.platforms[map.platformCount].type = block;
        map.platformCount++;

        j += size - 1;
      }
    }
  }
  fclose(mapFile);
}

void Map_DrawPlatforms() {
  for (int i = 0; i < map.platformCount; i++) {
    for (int j = 0; j < map.platforms[i].size; j++) {
      SDL_Rect dest = { map.platforms[i].x + (32 * j), map.platforms[i].y, 32, map.platforms[i].h };
      Gfx_BlitTexture(map.brickTexture, &dest);
    }
  }
}

void Map_DrawMap() {
  Map_DrawPlatforms();
}