
#include "window.h"
#include "raylib.h"

WindowSettings window_init(void) {
  WindowSettings w;
  w.width = 800;
  w.height = 600;
  w.title = "Bebis64";
  InitWindow(w.width, w.height, w.title);

  return w;
}
