#ifndef BEBIS64_CORE_H
#define BEBIS64_CORE_H

#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "window.h"

typedef struct CoreContext {
  WindowSettings window;
  Renderer *renderer;
  Input    *input;
  Audio    *audio;
} CoreContext;

void core_run(void);

#endif // BEBIS64_CORE_H
