#ifndef BEBIS64_INPUT_H
#define BEBIS64_INPUT_H

typedef struct Input {
  void (*init)(void);
  void (*update)(void);
  void (*shutdown)(void);
  int  (*is_key_down)(int key);
  int  (*is_key_pressed)(int key);
  int  (*is_mouse_button_down)(int button);
} Input;

Input *input_get_raylib(void);

#endif // BEBIS64_INPUT_H
