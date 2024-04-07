#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.h"
#include "defs.h"
#include "structs.h"

void gfx_Init();
Graphics* gfx_GetGraphics();
SDL_Window* gfx_GetWindow();
SDL_Renderer* gfx_GetRenderer();
SDL_Texture* gfx_LoadTexture(char* filepath);
void gfx_ClearRend();
void gfx_BlitTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);
void gfx_PresentRend();
void gfx_Cleanup();

#endif