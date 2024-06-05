#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "common.h"
#include "defs.h"
#include "joshim.h"
#include "structs.h"
#include "enums.h"
#include "input.h"
#include "map.h"
#include "text.h"
#include "menu.h"

void Game_Start();
void Game_Init();
void Game_GameLoop();
void Game_Cleanup();
void Game_ResetAll(Game* game);
void Game_HandleDeath(Game* game);


#endif