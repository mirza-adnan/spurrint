#ifndef MENU_H
#define MENU_H

#include "structs.h"
#include "common.h"
#include "graphics.h"
#include "enums.h"
#include "text.h"
#include "defs.h"

void Menu_Init();
void Menu_DrawMenu();
MenuOption* Menu_GetOptions();
void Menu_Cleanup();

#endif