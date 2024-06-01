#ifndef TEXT_H
#define TEXT_H

#include "structs.h"
#include "enums.h"
#include "common.h"
#include "graphics.h"
#include "game.h"
#include "defs.h"

void Text_DrawScore(Game* game);
void Text_DrawText(bool center, int x, int y, char* text, SDL_Color color, FontSize size);
void Text_Init();

#endif