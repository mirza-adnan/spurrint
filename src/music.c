#include "music.h"

Music music;

void Music_Init() {
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
  music.bg = Mix_LoadWAV("./src/assets/sounds/bg.mp3");
  music.jump = Mix_LoadMUS("./src/assets/sounds/jump.mp3");
  music.collect = Mix_LoadMUS("./src/assets/sounds/collect.mp3");
  music.damage = Mix_LoadMUS("./src/assets/sounds/damage.mp3");
  if (music.bg) {
    Mix_VolumeChunk(music.bg, 50);
  }
  else {
    printf("Cannot load bg music\n");
  }
  Mix_VolumeMusic(38);
}

void Music_Jump() {
  Mix_PlayMusic(music.jump, 0);
}

void Music_Collect() {
  Mix_PlayMusic(music.collect, 0);
}

void Music_Damage() {
  Mix_PlayMusic(music.damage, 0);
}

void Music_Play() {
  music.isPlaying = true;
  Mix_PlayChannel(-1, music.bg, -1);
}

void Music_Stop() {
  music.isPlaying = false;
  Mix_HaltChannel(-1);
}

bool Music_IsPlaying() {
  return music.isPlaying;
}

void Music_Cleanup() {
  Mix_FreeChunk(music.bg);
  Mix_FreeMusic(music.jump);
  Mix_FreeMusic(music.collect);
  Mix_FreeMusic(music.damage);
}