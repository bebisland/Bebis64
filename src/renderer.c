#include "renderer.h"
#include "raylib.h"

static void renderer_init(int width, int height, const char *title,
                          unsigned char flags) {
  SetConfigFlags(flags);
  InitWindow(width, height, title);
}

static void renderer_begin(void) { BeginDrawing(); }

static void renderer_clear(void) { ClearBackground(BLACK); }

static void renderer_end(void) { EndDrawing(); }

static void renderer_shutdown(void) { CloseWindow(); }

static int renderer_should_close(void) { return WindowShouldClose(); }

static float renderer_get_delta(void) { return GetFrameTime(); }

static Renderer renderer_raylib = {
    renderer_init,     renderer_begin,        renderer_clear,     renderer_end,
    renderer_shutdown, renderer_should_close, renderer_get_delta, 0};

Renderer *renderer_get_raylib(void) { return &renderer_raylib; }
