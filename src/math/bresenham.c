#include "canim.h"

static void set_disk_brush(t_canim *canim, int cx, int cy, int stroke_width, t_rgb color) {
	float radius = stroke_width / 2.0f;
	int	  ir = (int)ceilf(radius);
	for (int dy = -ir; dy <= ir; dy++) {
		for (int dx = -ir; dx <= ir; dx++) {
			if (dx * dx + dy * dy <= radius * radius) {
				set_pixel(canim, cx + dx, cy + dy, color.r, color.g, color.b);
			}
		}
	}
}

static void set_brush(t_canim *canim, int cx, int cy, int stroke_width, t_rgb color) {
	int half = stroke_width / 2;
	for (int dy = -half; dy <= half; dy++) {
		for (int dx = -half; dx <= half; dx++) {
			set_pixel(canim, cx + dx, cy + dy, color.r, color.g, color.b);
		}
	}
}

void render_line_bresen(t_canim *canim, t_path *path, t_point p1, t_point p2) {
	int x1 = (int)p1.x;
	int y1 = (int)p1.y;
	int x2 = (int)p2.x;
	int y2 = (int)p2.y;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;

	int err = dx - dy;

	while (1) {
		if (DISK_BRUSH)
			set_disk_brush(canim, x1, y1, path->stroke_width, path->stroke);
		else
			set_brush(canim, x1, y1, path->stroke_width, path->stroke);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
	(void)path;
}
