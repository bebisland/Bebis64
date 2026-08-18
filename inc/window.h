#ifndef BEBIS64_WINDOW_H
#define BEBIS64_WINDOW_H

typedef struct WindowSettings {
	int width;
	int height;
	char *title;
	unsigned char flags;
} WindowSettings;

WindowSettings window_init(void);

#endif // BEBIS64_WINDOW_H
