#include "core.h"
#include "raylib.h"
#include "window.h"

static CoreContext *core_ctx_get(void) {
  static CoreContext ctx = {0};
  return &ctx;
}

static void core_init(void) {
  CoreContext *ctx = core_ctx_get();
  SetTraceLogLevel(LOG_ERROR);

  ctx->window = window_init();
}

static void core_unload(void) { CloseWindow(); }

static void core_render(void) {
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}

static void core_loop(void) {
  while (!WindowShouldClose()) {
    core_render();
  }
}

void core_run(void) {
  core_init();
  core_loop();
  core_unload();
}
