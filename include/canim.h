#ifndef CANIM_H
#define CANIM_H

#include <GLFW/glfw3.h>
#include <fcntl.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifndef DEBUG
#define DEBUG false
#endif

#define WIDTH 720
#define HEIGHT 480
#define GLFW_CANIM_MAJOR 2
#define GLFW_CANIM_MINOR 0

typedef struct s_point {
	float x;
	float y;
} t_point;

typedef struct s_canim {
	GLFWwindow	 *window;
	GLuint		  tex;
	unsigned char pixels[WIDTH * HEIGHT * 3];
	size_t		  frame;
	double		  start_time;
	double		  last_frame;
} t_canim;

typedef enum e_segtype { SEG_MOVETO, SEG_LINETO, SEG_CUBIC, SEG_QUADRATIC, SEG_CLOSE } t_segtype;

typedef struct s_segment {
	t_segtype type;
	// for LINETO: endpoint in p[0]
	// for CUBIC:  control1 in p[0], control2 in p[1], endpoint in p[2]
	t_point p[3];

	struct s_segment *prev;
	struct s_segment *next;
} t_segment;

typedef struct s_path {
	t_segment *head;
	t_segment *tail;
	bool	   closed;
} t_path;

void mainloop(t_canim *canim);
void quadratic_bezier(t_point *points, t_point p, t_point q, t_point s, int step);
void cubic_bezier(t_point *points, t_point p1, t_point p2, t_point p3, t_point p4, int step);
void set_pixel(t_canim *canim, int x, int y, unsigned char r, unsigned char g, unsigned char b);
void render_path(t_canim *canim);

#endif
