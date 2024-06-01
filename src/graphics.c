#include "graphics.h"

Graphics graphics;

void Gfx_Init() {
  graphics.window = SDL_CreateWindow("Spurrint", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (graphics.window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
  }

  graphics.renderer = SDL_CreateRenderer(graphics.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (graphics.renderer == NULL) {
    printf("Error creating renderer: %s\n", SDL_GetError());
  }
}

Graphics* Gfx_GetGraphics() {
  return &graphics;
}

SDL_Window* Gfx_GetWindow() {
  return graphics.window;
}

SDL_Renderer* Gfx_GetRenderer() {
  return graphics.renderer;
}

SDL_Texture* Gfx_LoadTexture(char* filepath) {
  SDL_Texture* texture = IMG_LoadTexture(graphics.renderer, filepath);
  if (texture == NULL) {
    printf("Error loading texture %s: %s\n", filepath, IMG_GetError());
  }
  return texture;
}

void Gfx_SetColor(int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(graphics.renderer, r, g, b, a);
}

void Gfx_ClearRend() {
  SDL_RenderClear(graphics.renderer);
}

void Gfx_BlitTexture(SDL_Texture* texture, SDL_Rect* dest) {
  SDL_RenderCopy(graphics.renderer, texture, NULL, dest);
}

void Gfx_PresentRend() {
  SDL_RenderPresent(graphics.renderer);
}

void Gfx_Cleanup() {
  SDL_DestroyRenderer(graphics.renderer);
  SDL_DestroyWindow(graphics.window);
}