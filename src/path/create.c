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
	} else if (segtype == SEG_QUADRATIC) {
		segment->p[0] = points[0];
		segment->p[1] = points[1];
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

t_point *create_2_points(float x1, float y1, float x2, float y2) {
	t_point *points = malloc(2 * sizeof(t_point));

	if (!points)
		return NULL;
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	return points;
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
	/*path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(200, 200)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(100, 100, 400, 200, 400, 100)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(162, 14, 204.88,
	 * 314.159, 42.42, 8.590)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(300, 200)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(12, 55.6, 225, 450, 111, 512)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(100, 100)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(100, 300)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(200, 300)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(200, 0)));*/
	path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(0, 400)));
	/*path = add_seg_to_path(path, create_segment(SEG_QUADRATIC, create_2_points(0, 0, 400, 0)));*/
	path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(100, 100, 400, 300, 600, 400)));
	path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
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

#define MAX_POINTS 1000

void render_segment(t_canim *canim, t_path *path, t_segment *segment) {
	if (!segment->prev)
		return;

	t_point points[MAX_POINTS];
	int		count = 0;
	float	tol = 0.01f;	 // tolérance en pixels (ajuste selon la précision voulue)

	if (segment->type == SEG_CUBIC) {
		if (segment->prev->type == SEG_CUBIC) {
			points[count++] = segment->prev->p[2];
			cubic_adaptive(segment->prev->p[2], segment->p[0], segment->p[1], segment->p[2], tol, points, &count);
		} else if (segment->prev->type == SEG_QUADRATIC) {
			points[count++] = segment->prev->p[1];
			cubic_adaptive(segment->prev->p[1], segment->p[0], segment->p[1], segment->p[2], tol, points, &count);
		} else {
			points[count++] = segment->prev->p[0];
			cubic_adaptive(segment->prev->p[0], segment->p[0], segment->p[1], segment->p[2], tol, points, &count);
		}
		for (int i = 0; i < count - 1; i++)
			render_line_wu(canim, points[i], points[i + 1]);
	} else if (segment->type == SEG_QUADRATIC) {
		if (segment->prev->type == SEG_CUBIC) {
			points[count++] = segment->prev->p[2];
			quadratic_adaptive(segment->prev->p[2], segment->p[0], segment->p[1], tol, points, &count);
		} else if (segment->prev->type == SEG_QUADRATIC) {
			points[count++] = segment->prev->p[1];
			quadratic_adaptive(segment->prev->p[1], segment->p[0], segment->p[1], tol, points, &count);
		} else {
			points[count++] = segment->prev->p[0];
			quadratic_adaptive(segment->prev->p[0], segment->p[0], segment->p[1], tol, points, &count);
		}
		for (int i = 0; i < count - 1; i++)
			render_line_wu(canim, points[i], points[i + 1]);
	} else if (segment->type == SEG_LINETO) {
		if (segment->prev->type == SEG_CUBIC)
			render_line_wu(canim, segment->prev->p[2], segment->p[0]);
		else if (segment->prev->type == SEG_QUADRATIC)
			render_line_wu(canim, segment->prev->p[1], segment->p[0]);
		else
			render_line_wu(canim, segment->prev->p[0], segment->p[0]);
	} else if (segment->type == SEG_CLOSE) {
		t_segment *cursor = segment;
		while (cursor->prev) {
			if (cursor->type == SEG_MOVETO)
				break;
			cursor = cursor->prev;
		}
		segment->p[0] = cursor->p[0];
		if (segment->prev->type == SEG_CUBIC) {
			render_line_wu(canim, segment->prev->p[2], segment->p[0]);
		} else if (segment->prev->type == SEG_QUADRATIC) {
			render_line_wu(canim, segment->prev->p[1], segment->p[0]);
		} else {
			render_line_wu(canim, segment->prev->p[0], segment->p[0]);
		}
	}
	(void)path;
}

void add_last_dlst(t_segment *head, t_segment *tail) {
	while (head->next)
		head = head->next;
	head->next = tail;
	tail->prev = head;
}

t_path *create_circle(t_point c, float r) {
	float k = 0.5522847498f;
	float cc = r * k;

	t_point moveto[4] = {{c.x, c.y - r}, {c.x + r, c.y}, {c.x, c.y + r}, {c.x - r, c.y}};

	t_point controls[4][2] = {{{c.x + cc, c.y - r}, {c.x + r, c.y - cc}},
							  {{c.x + r, c.y + cc}, {c.x + cc, c.y + r}},
							  {{c.x - cc, c.y + r}, {c.x - r, c.y + cc}},
							  {{c.x - r, c.y - cc}, {c.x - cc, c.y - r}}};

	t_path *path = create_path();
	add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(moveto[0].x, moveto[0].y)));

	for (int i = 0; i < 4; i++) {
		t_point *pts = create_3_points(controls[i][0].x, controls[i][0].y, controls[i][1].x, controls[i][1].y,
									   moveto[(i + 1) % 4].x, moveto[(i + 1) % 4].y);
		add_seg_to_path(path, create_segment(SEG_CUBIC, pts));
	}
	add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));

	return path;
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
	path = create_circle((t_point){WIDTH / 2, HEIGHT / 2}, 200);
	segment = path->head;
	while (segment) {
		render_segment(canim, path, segment);
		segment = segment->next;
	}
}
