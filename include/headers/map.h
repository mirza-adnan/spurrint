#ifndef MAP_H
#define MAP_H

#include "structs.h"
#include "common.h"
#include "graphics.h"
#include "enums.h"

void Map_Init(Map* map);
void Map_DrawPlatforms(Map* map);
void Map_DetectCollision(Game* game);
void Map_DrawMap(Map* map);

#endif