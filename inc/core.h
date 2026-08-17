#ifndef BEBIS64_CORE_H
#define BEBIS64_CORE_H

#include "window.h"

typedef struct CoreContext {
  WindowSettings window;
} CoreContext;

void core_run(void);

#endif // BEBIS64_CORE_H
