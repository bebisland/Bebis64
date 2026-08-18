#ifndef BEBIS64_AUDIO_H
#define BEBIS64_AUDIO_H

#include "result.h"

typedef struct Audio {
	Result (*init)(void);
	void (*update)(void);
	Result (*shutdown)(void);
} Audio;

Audio *audio_get_raylib(void);

#endif // BEBIS64_AUDIO_H
