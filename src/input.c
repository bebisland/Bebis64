#include "input.h"
#include <stddef.h>

static Input input_raylib = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

Input *input_get_raylib(void) {
  return &input_raylib;
}
