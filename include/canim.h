#ifndef CANIM_H
#define CANIM_H

#include <GLFW/glfw3.h>
#include <fcntl.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <math.h>
#include <memory.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG false
#endif

#define WIDTH 1280
#define HEIGHT 720
#define GLFW_CANIM_MAJOR 3
#define GLFW_CANIM_MINOR 0

#define MAX_POINTS 1000

#define LINE_WU false
#define DISK_BRUSH true

typedef struct s_point {
	float x;
	float y;
} t_point;

typedef struct s_rgb {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} t_rgb;

typedef struct s_rgba {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} t_rgba;

typedef struct s_canim {
	GLFWwindow	 *window;
	GLuint		  tex;
	unsigned char pixels[WIDTH * HEIGHT * 4];
	size_t		  frame;
	double		  start_time;
	double		  last_frame;
} t_canim;

typedef enum e_segtype {
	SEG_MOVETO,
	SEG_LINETO,
	SEG_CUBIC,
	SEG_QUADRATIC,
	SEG_CLOSE,
	SEG_SMOOTH_QUADRATIC,
	SEG_SMOOTH_CUBIC
} t_segtype;

typedef struct s_segment {
	t_segtype type;
	// for LINETO: endpoint in p[0]
	// for QUADRATIC:  control1 in p[0], ENDPOINT in p[1]
	// for CUBIC:  control1 in p[0], control2 in p[1], endpoint in p[2]
	t_point p[3];

	struct s_segment *prev;
	struct s_segment *next;
} t_segment;

typedef struct s_animate t_animate;
typedef struct s_path {
	t_segment *head;
	t_segment *tail;
	t_rgb	   stroke;
	int		   stroke_width;
	uint8_t	   stroke_opacity;
	bool	   closed;
	t_animate *animation;
} t_path;

typedef struct s_shape {
	t_path		   *path;
	struct s_shape *next;
} t_shape;

typedef enum e_animtype {
	CREATE,
} t_animtype;

typedef enum e_animtiming {
	LINEAR,
	EASE_IN,
	EASE_OUT,
	EASE_IN_OUT
} t_animtiming;

typedef enum e_animrepeat {
	ONCE,
	INFINITE
} t_animrepeat;

typedef struct s_animate {
	t_animtype		  type;
	double			  start;
	double			  duration;
	t_animtiming	  timing;
	t_animrepeat	  repeat;
	struct s_animate *next;
} t_animate;

void mainloop(t_canim *canim);
void set_pixel(t_canim *canim, t_point co, t_rgba colora);
void render_shapes(t_canim *canim);

void quadratic_adaptive(t_point p, t_point q, t_point r, float tol, t_point *points, int *count);
void cubic_adaptive(t_point p1, t_point p2, t_point p3, t_point p4, float tol, t_point *points, int *count);

void render_line_bresen(t_canim *canim, t_path *path, t_point p1, t_point p2);
void render_line_wu(t_canim *canim, t_path *path, t_point p1, t_point p2);

t_rgb  color_from_hex(int hex);
t_rgb  color_from_all(uint8_t r, uint8_t g, uint8_t b);
t_rgba colora_from_hex(int hex);
t_rgba colora_from_all(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_rgba colora_from_color(t_rgb color, uint8_t a);

t_animate *create_animation(t_animtype type, double start, double duration, double timing, t_animrepeat repeat);
t_animate *add_animation(t_animate *head, t_animate *new);

#endif
