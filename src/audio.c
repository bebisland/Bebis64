#include "audio.h"
#include <stddef.h>

static Audio audio_raylib = {
  NULL,
  NULL,
  NULL
};

Audio *audio_get_raylib(void) {
  return &audio_raylib;
}
