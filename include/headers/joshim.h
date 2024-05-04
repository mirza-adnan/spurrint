#ifndef JOSHIM_H
#define JOSHIM_H

#include "common.h"
#include "graphics.h"
#include "structs.h"
#include "enums.h"
#include "defs.h"

void Joshim_Init(Joshim* joshim);
void Joshim_Draw(Game* game);
void Joshim_Move(Game* game);
void Joshim_Cleanup(Joshim* joshim);

#endif