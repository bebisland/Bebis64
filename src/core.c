#include "core.h"
#include "raylib.h"

static CoreContext *core_ctx_get(void) {
  static CoreContext ctx = {0};
  return &ctx;
}

static void core_init(void) {
  CoreContext *ctx = core_ctx_get();
  SetTraceLogLevel(LOG_ERROR);

  ctx->renderer = renderer_get_raylib();
  ctx->input    = input_get_raylib();
  ctx->audio    = audio_get_raylib();

  ctx->window.width  = 800;
  ctx->window.height = 600;
  ctx->window.title  = "Bebis64";

  ctx->renderer->init(ctx->window.width, ctx->window.height, ctx->window.title);
}

static void core_unload(void) {
  CoreContext *ctx = core_ctx_get();
  if (ctx->renderer->shutdown) ctx->renderer->shutdown();
}

static void core_render(void) {
  CoreContext *ctx = core_ctx_get();
  ctx->renderer->begin();
  ctx->renderer->clear();
  ctx->renderer->end();
}

static void core_loop(void) {
  CoreContext *ctx = core_ctx_get();
  while (!ctx->renderer->should_close()) {
    core_render();
  }
}

void core_run(void) {
  core_init();
  core_loop();
  core_unload();
}
