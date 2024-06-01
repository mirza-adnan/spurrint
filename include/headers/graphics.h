#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "defs.h"
#include "structs.h"
#include "enums.h"

void Gfx_Init();
Graphics* Gfx_GetGraphics();
SDL_Window* Gfx_GetWindow();
SDL_Renderer* Gfx_GetRenderer();
SDL_Texture* Gfx_LoadTexture(char* filepath);
void Gfx_SetColor(int r, int g, int b, int a);
void Gfx_ClearRend();
void Gfx_BlitTexture(SDL_Texture* texture, SDL_Rect* dest);
void Gfx_PresentRend();
void Gfx_Cleanup();

#endif