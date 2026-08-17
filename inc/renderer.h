#ifndef BEBIS64_RENDERER_H
#define BEBIS64_RENDERER_H

typedef struct Renderer {
  void (*init)(int width, int height, const char *title);
  void (*begin)(void);
  void (*clear)(void);
  void (*end)(void);
  void (*shutdown)(void);
  int  (*should_close)(void);
} Renderer;

Renderer *renderer_get_raylib(void);

#endif // BEBIS64_RENDERER_H
