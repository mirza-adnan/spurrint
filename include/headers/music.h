#ifndef MUSIC_H
#define MUSIC_H

#include "common.h"
#include "structs.h"
#include "enums.h"

void Music_Init();
void Music_Cleanup();
void Music_Play();
void Music_Stop();
void Music_Jump();
void Music_Collect();
void Music_Damage();
bool Music_IsPlaying();


#endif