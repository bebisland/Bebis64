#include "core.h"
#include "log.h"
#include "raylib.h"

#define CORE_DEFAULT_FIXED_STEP (1.0f / 60.0f)

static CoreContext *core_ctx_get(void) {
  static CoreContext ctx = {0};
  return &ctx;
}

static void core_init(void) {
  CoreContext *ctx = core_ctx_get();

  log_init();
  log_set_level(LOG_LEVEL_INFO);
  SetTraceLogLevel(LOG_NONE);
  log_info("Engine starting");

  ctx->renderer = renderer_get_raylib();
  ctx->input = input_get_raylib();
  ctx->audio = audio_get_raylib();

  ctx->window.width = 800;
  ctx->window.height = 600;
  ctx->window.title = "Bebis64";
  ctx->window.flags = FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT;

  ctx->fixed_step = CORE_DEFAULT_FIXED_STEP;
  ctx->accumulator = 0.0f;
  ctx->frame_time = 0.0f;

  log_info("Creating window: %dx%d [%s]", ctx->window.width, ctx->window.height,
           ctx->window.title);
  ctx->renderer->init(ctx->window.width, ctx->window.height, ctx->window.title,
                      ctx->window.flags);
  log_info("Engine ready");
}

static void core_unload(void) {
  CoreContext *ctx = core_ctx_get();
  log_info("Engine shutting down");
  if (ctx->renderer->shutdown)
    ctx->renderer->shutdown();
  log_shutdown();
}

static void core_update(float dt) { (void)dt; }

static void core_render(void) {
  CoreContext *ctx = core_ctx_get();
  ctx->renderer->begin();
  ctx->renderer->clear();
  ctx->renderer->end();
}

static void core_loop(void) {
  CoreContext *ctx = core_ctx_get();

  while (!ctx->renderer->should_close()) {
    ctx->frame_time = ctx->renderer->get_delta();
    ctx->accumulator = ctx->frame_time;

    while (ctx->accumulator >= ctx->fixed_step) {
      core_update(ctx->fixed_step);
      ctx->accumulator -= ctx->fixed_step;
    }

    core_render();
  }
}

void core_run(void) {
  core_init();
  core_loop();
  core_unload();
}
