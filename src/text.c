#include "text.h"

Text textWrapper;

void Text_Init() {
  textWrapper.fonts[FONT_SIZE_48_BOLD] = TTF_OpenFont("./src/assets/fonts/Crazy-Pixel.ttf", 48);
  textWrapper.fonts[FONT_SIZE_48] = TTF_OpenFont("./src/assets/fonts/Crazy-Pixel.ttf", 48);
  textWrapper.fonts[FONT_SIZE_36] = TTF_OpenFont("./src/assets/fonts/Crazy-Pixel.ttf", 36);
  TTF_SetFontStyle(textWrapper.fonts[FONT_SIZE_48_BOLD], TTF_STYLE_BOLD);

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

void Text_DrawText(bool center, int x, int y, char* text, SDL_Color color, FontSize size) {
  SDL_Texture* label = Text_CreateLabel(text, color, size);

  SDL_Rect textRect;
  //SDL_QueryTexture(label, NULL, NULL, &textRect.w, &textRect.h);
  TTF_SizeText(textWrapper.fonts[size], text, &textRect.w, &textRect.h);
  textRect.x = x > -1 ? x : (SCREEN_WIDTH / 2) - (textRect.w / 2);
  textRect.y = y > -1 ? y : (SCREEN_HEIGHT / 2) - (textRect.h / 2);

  Gfx_BlitTexture(label, &textRect);

  SDL_DestroyTexture(label);
}

void Text_DrawScore(Game* game) {
  char str[6];
  sprintf(str, "%d", game->score);

  SDL_Color black = { 0, 0, 0, 255 };
  Text_DrawText(false, 560, 5, str, black, FONT_SIZE_48_BOLD);
}

void Text_Cleanup() {
  for (int i = 0; i < FONT_SIZE_TOTAL; i++) {
    TTF_CloseFont(textWrapper.fonts[i]);
  }
}