#include "graphics.h"

Graphics graphics;

void gfx_Init() {
  graphics.window = SDL_CreateWindow("Spurrint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (graphics.window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
  }

  graphics.renderer = SDL_CreateRenderer(graphics.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (graphics.renderer == NULL) {
    printf("Error creating renderer: %s\n", SDL_GetError());
  }
}

Graphics* gfx_GetGraphics() {
  return &graphics;
}

SDL_Window* gfx_GetWindow() {
  return graphics.window;
}

SDL_Renderer* gfx_GetRenderer() {
  return graphics.renderer;
}

SDL_Texture* gfx_LoadTexture(char* filepath) {
  SDL_Texture* texture = IMG_LoadTexture(graphics.renderer, filepath);
  if (texture == NULL) {
    printf("Error loading texture %s: %s\n", filepath, IMG_GetError());
  }
  return texture;
}

void gfx_ClearRend() {
  SDL_RenderClear(graphics.renderer);
}

void gfx_BlitTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest) {
  SDL_RenderCopy(graphics.renderer, texture, src, dest);
}

void gfx_PresentRend() {
  SDL_RenderPresent(graphics.renderer);
}