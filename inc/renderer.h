#ifndef BEBIS64_RENDERER_H
#define BEBIS64_RENDERER_H

typedef struct Renderer {
  void (*init)(int width, int height, const char *title, unsigned char flags);
  void (*begin)(void);
  void (*clear)(void);
  void (*end)(void);
  void (*shutdown)(void);
  int (*should_close)(void);
  float (*get_delta)(void);
  unsigned char flags;
} Renderer;

Renderer *renderer_get_raylib(void);

#endif // BEBIS64_RENDERER_H
