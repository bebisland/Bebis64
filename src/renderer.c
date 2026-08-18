#include "renderer.h"
#include "log.h"
#include "raylib.h"

static Result renderer_init(int width, int height, const char *title,
			    unsigned char flags)
{
	SetConfigFlags(flags);
	InitWindow(width, height, title);

	if (!IsWindowReady())
		return result_err(RESULT_ERR_INIT,
				  "Window initialization failed");

	log_info("Window created: %dx%d [%s]", width, height, title);
	return result_ok();
}

static void renderer_begin(void)
{
	BeginDrawing();
}

static void renderer_clear(void)
{
	ClearBackground(BLACK);
}

static void renderer_end(void)
{
	EndDrawing();
}

static Result renderer_shutdown(void)
{
	CloseWindow();
	log_info("Window destroyed");
	return result_ok();
}

static int renderer_should_close(void)
{
	return WindowShouldClose();
}

static float renderer_get_delta(void)
{
	return GetFrameTime();
}

static Renderer renderer_raylib = {
    renderer_init,     renderer_begin,	      renderer_clear,	  renderer_end,
    renderer_shutdown, renderer_should_close, renderer_get_delta, 0};

Renderer *renderer_get_raylib(void)
{
	return &renderer_raylib;
}
