#ifndef BEBIS64_CORE_H
#define BEBIS64_CORE_H

#include "audio.h"
#include "input.h"
#include "renderer.h"
#include "window.h"

typedef struct CoreContext {
  WindowSettings window;
  Renderer *renderer;
  Input *input;
  Audio *audio;
  float fixed_step;
  float accumulator;
  float frame_time;
} CoreContext;

void core_run(void);

#endif // BEBIS64_CORE_H
