#ifndef BEBIS64_wINDOW_H
#define BEBIS64_wINDOW_H

typedef struct WindowSettings {
  int width;
  int height;
  char *title;
  unsigned char flags;
} WindowSettings;

WindowSettings window_init(void);

#endif // BEBIS64_wINDOW_H
