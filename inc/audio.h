#ifndef BEBIS64_AUDIO_H
#define BEBIS64_AUDIO_H

typedef struct Audio {
  void (*init)(void);
  void (*update)(void);
  void (*shutdown)(void);
} Audio;

Audio *audio_get_raylib(void);

#endif // BEBIS64_AUDIO_H
