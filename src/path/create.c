#include "canim.h"

t_segment *create_segment(t_segtype segtype, t_point *points) {
	t_segment *segment;

	segment = malloc(sizeof(t_segment));
	if (!segment)
		return (NULL);
	segment->next = NULL;
	segment->prev = NULL;
	segment->type = segtype;
	if (segtype == SEG_MOVETO || segtype == SEG_LINETO) {
		segment->p[0] = points[0];
	} else if (segtype == SEG_CUBIC) {
		segment->p[0] = points[0];
		segment->p[1] = points[1];
		segment->p[2] = points[2];
	}
	return segment;
}

t_path *add_seg_to_path(t_path *path, t_segment *segment) {
	t_segment *cursor;

	if (!path || !segment)
		return (NULL);
	if (!path->head)
		path->head = segment;
	else {
		cursor = path->head;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = segment;
		segment->prev = cursor;
	}
	return path;
}

t_path *create_path(void) {
	t_path *path;

	path = malloc(sizeof(t_path));
	if (!path)
		return (NULL);
	path->closed = 0;
	path->head = NULL;
	return path;
}

t_point *create_point(float x, float y) {
	t_point *point;

	point = malloc(sizeof(t_point));
	if (!point)
		return NULL;
	point->x = x;
	point->y = y;
	return point;
}

t_point *create_3_points(float x1, float y1, float x2, float y2, float x3, float y3) {
	t_point *points = malloc(3 * sizeof(t_point));

	if (!points)
		return NULL;
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	points[2].x = x3;
	points[2].y = y3;
	return points;
}

t_path *simple_path(void) {
	t_path *path;

	path = create_path();
	path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(200, 200)));
	path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(100, 100, 400, 200, 400, 100)));
	path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(162, 14, 204.88, 314.159, 42.42, 8.590)));
	path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(300, 200)));
	path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(12, 55.6, 225, 450, 111, 512)));
	path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(100, 100)));
	path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(100, 300)));
	path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(200, 300)));
	path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
	path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(200, 0)));
	return path;
}

// bresenham implementtion (TODO switch to WU line)
void render_line(t_canim *canim, t_point p1, t_point p2) {
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
		set_pixel(canim, x1, y1, 255, 255, 255);
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
}

void render_segment(t_canim *canim, t_path *path, t_segment *segment) {
	if (!segment->prev)
		return;
	else {
		int		step = 1000;
		t_point points[step];
		if (segment->type == SEG_CUBIC) {
			if (segment->prev->type == SEG_CUBIC)
				cubic_bezier(points, segment->prev->p[2], segment->p[0], segment->p[1], segment->p[2], step);
			else
				cubic_bezier(points, segment->prev->p[0], segment->p[0], segment->p[1], segment->p[2], step);
			for (int i = 0; i < step; i++) {
				set_pixel(canim, points[i].x, points[i].y, 255, 255, 255);
			}
		} else if (segment->type == SEG_LINETO) {
			if (segment->prev->type == SEG_CUBIC) {
				render_line(canim, segment->prev->p[2], segment->p[0]);
			} else {
				render_line(canim, segment->prev->p[0], segment->p[0]);
			}
			set_pixel(canim, segment->p[0].x, segment->p[0].y, 255, 0, 0);
		} else if (segment->type == SEG_CLOSE) {
			t_segment *cursor;

			cursor = segment;
			while (cursor->prev) {
				if (cursor->type == SEG_MOVETO)
					break;
				cursor = cursor->prev;
			}
			segment->p[0] = cursor->p[0];
			if (segment->prev->type == SEG_CUBIC) {
				render_line(canim, segment->prev->p[2], segment->p[0]);
			} else {
				render_line(canim, segment->prev->p[0], segment->p[0]);
			}
		}
	}
	(void)path;
}

void render_path(t_canim *canim) {
	t_path	  *path;
	t_segment *segment;

	path = simple_path();
	segment = path->head;
	while (segment) {
		render_segment(canim, path, segment);
		segment = segment->next;
	}
}
