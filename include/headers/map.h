#ifndef MAP_H
#define MAP_H

#include "structs.h"
#include "common.h"
#include "graphics.h"
#include "enums.h"
#include "utils.h"
#include "text.h"

void Map_Init(Map* map);
void Map_DrawPlatforms(Game* game);
void Map_DrawCollectibles(Game* game);
void Map_DrawSky(Game* game);
void Map_CollectCollectible(Game* game);
void Map_DetectCollision(Game* game);
void Map_DrawMap(Game* game);
void Map_Cleanup(Map* map);

#endif