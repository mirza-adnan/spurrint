#include "menu.h"

Menu menu;

void Menu_Init() {
  strcpy(menu.options[0].name, "PLAY");
  menu.options[0].type = MENU_BUTTON_PLAY;
  menu.options[0].selected = true;

  strcpy(menu.options[1].name, "EXIT");
  menu.options[1].type = MENU_BUTTON_EXIT;
  menu.options[1].selected = false;

  strcpy(menu.pauseOptions[0].name, "CONTINUE");
  menu.pauseOptions[0].type = PAUSE_BUTTON_CONTINUE;
  menu.pauseOptions[0].selected = true;

  strcpy(menu.pauseOptions[1].name, "RESTART");
  menu.pauseOptions[1].type = PAUSE_BUTTON_RESTART;
  menu.pauseOptions[1].selected = false;

  strcpy(menu.pauseOptions[2].name, "EXIT");
  menu.pauseOptions[2].type = PAUSE_BUTTON_EXIT;
  menu.pauseOptions[2].selected = false;

  menu.textures[MENU_TEXTURE_TITLE] = Gfx_LoadTexture("./src/assets/components/title.png");
  menu.textures[MENU_TEXTURE_ICON] = Gfx_LoadTexture("./src/assets/components/icon.png");
  menu.textures[MENU_TEXTURE_BUTTON] = Gfx_LoadTexture("./src/assets/components/button.png");
}

void Menu_DrawTitle() {
  SDL_Rect titleRect;
  SDL_QueryTexture(menu.textures[MENU_TEXTURE_TITLE], NULL, NULL, &titleRect.w, &titleRect.h);
  titleRect.w *= 0.6;
  titleRect.h *= 0.6;

  titleRect.x = (SCREEN_WIDTH / 2) - (titleRect.w / 2);
  titleRect.y = 80;

  Gfx_BlitTexture(menu.textures[MENU_TEXTURE_TITLE], &titleRect);
}

void Menu_DrawIcon() {
  SDL_Rect iconRect;
  SDL_QueryTexture(menu.textures[MENU_TEXTURE_ICON], NULL, NULL, &iconRect.w, &iconRect.h);

  iconRect.w *= 2;
  iconRect.h *= 2;

  iconRect.x = (SCREEN_WIDTH / 2) - (iconRect.w / 2);
  iconRect.y = 150;

  Gfx_BlitTexture(menu.textures[MENU_TEXTURE_ICON], &iconRect);
}

void Menu_DrawButtons() {
  for (int i = 0; i < MENU_BUTTON_TOTAL; i++) {
    SDL_Rect btnRect;
    SDL_QueryTexture(menu.textures[MENU_TEXTURE_BUTTON], NULL, NULL, &btnRect.w, &btnRect.h);

    btnRect.w *= 2.3;
    btnRect.h *= 2.3;

    btnRect.x = (SCREEN_WIDTH / 2) - (btnRect.w / 2);
    btnRect.y = 250 + (70 * i);

    menu.options[i].x = btnRect.x;
    menu.options[i].y = btnRect.y;
    menu.options[i].w = btnRect.w;
    menu.options[i].h = btnRect.h;

    Gfx_BlitTexture(menu.textures[MENU_TEXTURE_BUTTON], &btnRect);

    SDL_Color active = { 255, 238, 200, 255 };
    SDL_Color black = { 0, 0, 0, 255 };

    Text_DrawText(true, -1, 230 + (70 * i), menu.options[i].name, menu.options[i].selected ? active : black, FONT_SIZE_48);
  }
}

void Menu_DrawPauseButtons() {
  for (int i = 0; i < PAUSE_BUTTON_TOTAL; i++) {
    SDL_Rect btnRect;
    SDL_QueryTexture(menu.textures[MENU_TEXTURE_BUTTON], NULL, NULL, &btnRect.w, &btnRect.h);

    btnRect.w *= 2.3;
    btnRect.h *= 2.3;

    btnRect.x = (SCREEN_WIDTH / 2) - (btnRect.w / 2);
    btnRect.y = 250 + (70 * i);

    menu.pauseOptions[i].x = btnRect.x;
    menu.pauseOptions[i].y = btnRect.y;
    menu.pauseOptions[i].w = btnRect.w;
    menu.pauseOptions[i].h = btnRect.h;

    Gfx_BlitTexture(menu.textures[MENU_TEXTURE_BUTTON], &btnRect);

    SDL_Color active = { 255, 238, 200, 255 };
    SDL_Color black = { 0, 0, 0, 255 };

    Text_DrawText(true, -1, 230 + (70 * i), menu.pauseOptions[i].name, menu.pauseOptions[i].selected ? active : black, FONT_SIZE_48);
  }
}

void Menu_DrawMenu() {
  Gfx_SetColor(255, 238, 200, 255);
  Gfx_ClearRend();
  Menu_DrawTitle();
  Menu_DrawIcon();
  Menu_DrawButtons();
}

void Menu_DrawPauseMenu() {
  Gfx_SetColor(255, 238, 200, 255);
  Gfx_ClearRend();
  Menu_DrawTitle();
  Menu_DrawIcon();
  Menu_DrawPauseButtons();
}

MenuOption* Menu_GetOptions() {
  return menu.options;
}

PauseOption* Menu_GetPauseOptions() {
  return menu.pauseOptions;
}

void Menu_Cleanup() {
  for (int i = 0; i < MENU_TEXTURE_TOTAL; i++) {
    SDL_DestroyTexture(menu.textures[i]);
  }
}