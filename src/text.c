#include "text.h"

Text textWrapper;

void Text_Init() {
  textWrapper.fonts[FONT_SIZE_48] = TTF_OpenFont("./src/assets/fonts/Crazy-Pixel.ttf", 52);
  TTF_SetFontStyle(textWrapper.fonts[FONT_SIZE_48], TTF_STYLE_BOLD);

  for (int i = 0; i < FONT_SIZE_TOTAL; i++) {
    if (textWrapper.fonts[i] == NULL) {
      printf("Error opening font %d\n", i);
    }
  }
}

SDL_Texture* Text_CreateLabel(const char* msg, SDL_Color color, FontSize size) {
  SDL_Surface* temp = TTF_RenderText_Blended(textWrapper.fonts[size], msg, color);
  if (temp == NULL) {
    printf("Error creating surface: %s\n", SDL_GetError());
  }

  SDL_Texture* label = SDL_CreateTextureFromSurface(Gfx_GetRenderer(), temp);
  SDL_FreeSurface(temp);

  if (label == NULL) {
    printf("Error creating label: %s\n", SDL_GetError());
  }

  return label;
}

void Text_DrawText(int x, int y, char* text, SDL_Color color, FontSize size) {
  SDL_Texture* label = Text_CreateLabel(text, color, size);

  SDL_Rect textRect = { x, y, 0, 0 };
  SDL_QueryTexture(label, NULL, NULL, &textRect.w, &textRect.h);
  Gfx_BlitTexture(label, &textRect);

  SDL_DestroyTexture(label);
}

void Text_DrawScore(Game* game) {
  char str[6];
  sprintf(str, "%d", game->score);

  SDL_Color black = { 0, 0, 0, 255 };
  Text_DrawText(560, 5, str, black, FONT_SIZE_48);
}

void Text_Cleanup() {
  for (int i = 0; i < FONT_SIZE_TOTAL; i++) {
    TTF_CloseFont(textWrapper.fonts[i]);
  }
}