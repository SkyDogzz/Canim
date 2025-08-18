#ifndef CANIM_H
#define CANIM_H

#include <GLFW/glfw3.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG false
#endif

#define WIDTH 720
#define HEIGHT 480
#define GLFW_CANIM_MAJOR 2
#define GLFW_CANIM_MINOR 0

typedef struct s_canim {
	GLFWwindow	 *window;
	GLuint		  tex;
	unsigned char pixels[WIDTH * HEIGHT * 3];
	size_t		  frame;
	double		  start_time;
	double		  last_frame;
} t_canim;

void mainloop(t_canim *canim);

#endif
