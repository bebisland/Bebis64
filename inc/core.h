#ifndef BEBIS64_CORE_H
#define BEBIS64_CORE_H

#include "arena.h"
#include "audio.h"
#include "input.h"
#include "renderer.h"
#include "result.h"
#include "window.h"

typedef struct CoreContext {
	WindowSettings window;
	Renderer *renderer;
	Input *input;
	Audio *audio;
	Arena frame_arena;
	float fixed_step;
	float accumulator;
	float frame_time;
} CoreContext;

Result core_run(void);

#endif // BEBIS64_CORE_H
