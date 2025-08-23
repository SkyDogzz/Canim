#include "canim.h"

t_segment *create_segment(t_segtype segtype, t_point *points) {
	t_segment *segment = malloc(sizeof(t_segment));
	if (!segment)
		return NULL;
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
	} else if (segtype == SEG_SMOOTH_QUADRATIC) {
		segment->p[0] = points[0];
	} else if (segtype == SEG_SMOOTH_CUBIC) {
		segment->p[0] = points[0];
		segment->p[1] = points[1];
	}
	return segment;
}

t_path *add_seg_to_path(t_path *path, t_segment *segment) {
	if (!path || !segment)
		return NULL;

	if (!path->head) {
		path->head = segment;
		path->tail = segment;
	} else {
		path->tail->next = segment;
		segment->prev = path->tail;
		path->tail = segment;
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
	path->stroke.r = 255;
	path->stroke.g = 255;
	path->stroke.b = 255;
	path->stroke_width = 1;
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

t_point *create_points(int counter, ...) {
	int		i = 0;
	va_list parametersInfos;
	va_start(parametersInfos, counter);

	if (counter < 0 || counter > 3) {
		printf("Cant create %d points\n", counter);
		return NULL;
	}
	t_point *points = malloc(sizeof(t_point) * 3);
	while (i < counter) {
		points[i] = (t_point)va_arg(parametersInfos, t_point);
		printf("%f %f\n", points[i].x, points[i].y);
		i++;
	}
	va_end(parametersInfos);
	return points;
}

t_point *create_pointss(int counter, t_point *array) {
	if (counter < 0 || counter > 3) {
		printf("Cant create %d points\n", counter);
		return NULL;
	}
	t_point *points = malloc(sizeof(t_point) * counter);
	if (!points)
		return NULL;
	for (int i = 0; i < counter; i++)
		points[i] = array[i];
	return points;
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
	/*pat h = add_seg_to_path(path, create_segment(SEG_MOVETO, create_points(1, (t_point){200, 200})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_pointss(1, (t_point[]){{400, 400}})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_points(1, (t_point){400, 400})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_points(1, (t_point){400, 400})));*/
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
	/*path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(0, 400)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_QUADRATIC, create_2_points(0, 0, 400, 0)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(100, 100, 400, 300, 600, 400)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));*/
	path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_pointss(1, (t_point[]){{150, 5}})));
	path = add_seg_to_path(path, create_segment(SEG_LINETO, create_pointss(1, (t_point[]){{75, 200}})));
	path = add_seg_to_path(path, create_segment(SEG_LINETO, create_pointss(1, (t_point[]){{225, 200}})));
	path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
	return path;
}

t_path *simple_path2(void) {
	t_path *path = create_path();
	path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(100, 200)));
	path = add_seg_to_path(path, create_segment(SEG_QUADRATIC, create_2_points(150, 100, 200, 200)));
	path = add_seg_to_path(path, create_segment(SEG_SMOOTH_QUADRATIC, create_point(300, 200)));
	path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(300, 300, 400, 300, 400, 200)));
	path = add_seg_to_path(path, create_segment(SEG_SMOOTH_CUBIC, create_2_points(500, 100, 600, 200)));
	path = add_seg_to_path(path, create_segment(SEG_SMOOTH_CUBIC, create_2_points(500, 100, 100, 500)));
	path = add_seg_to_path(path,
						   create_segment(SEG_SMOOTH_CUBIC, create_2_points(195.176, 392.0451, 429.0431, 17.0859716)));
	path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
	return path;
}

static t_point reflect_point(t_point ref, t_point anchor) {
	t_point r;
	r.x = 2 * anchor.x - ref.x;
	r.y = 2 * anchor.y - ref.y;
	return r;
}

void render_segment(t_canim *canim, t_path *path, t_segment *segment) {
	if (!segment->prev)
		return;

	void (*render_line_sel)(t_canim *canim, t_path *path, t_point p1, t_point p2);
	render_line_sel = LINE_WU ? &render_line_wu : &render_line_bresen;

	t_point points[MAX_POINTS];
	int		count = 0;
	float	tol = 0.01f;

	t_point anchor;
	if (segment->prev->type == SEG_CUBIC)
		anchor = segment->prev->p[2];
	else if (segment->prev->type == SEG_QUADRATIC || segment->prev->type == SEG_SMOOTH_CUBIC)
		anchor = segment->prev->p[1];
	else
		anchor = segment->prev->p[0];

	if (segment->type == SEG_CUBIC) {
		if (segment->prev->type == SEG_QUADRATIC) {
			segment->p[0] = reflect_point(segment->prev->p[0], anchor);
		} else if (segment->prev->type == SEG_CUBIC) {
			segment->p[0] = reflect_point(segment->prev->p[1], anchor);
		}

		points[count++] = anchor;
		cubic_adaptive(anchor, segment->p[0], segment->p[1], segment->p[2], tol, points, &count);
		for (int i = 0; i < count - 1; i++)
			render_line_sel(canim, path, points[i], points[i + 1]);

	} else if (segment->type == SEG_QUADRATIC) {
		if (segment->prev->type == SEG_CUBIC) {
			segment->p[0] = reflect_point(segment->prev->p[2], anchor);
		} else if (segment->prev->type == SEG_QUADRATIC) {
			segment->p[0] = reflect_point(segment->prev->p[0], anchor);
		}

		points[count++] = anchor;
		quadratic_adaptive(anchor, segment->p[0], segment->p[1], tol, points, &count);
		for (int i = 0; i < count - 1; i++)
			render_line_sel(canim, path, points[i], points[i + 1]);

	} else if (segment->type == SEG_LINETO) {
		render_line_sel(canim, path, anchor, segment->p[0]);

	} else if (segment->type == SEG_CLOSE) {
		t_segment *cursor = segment;
		while (cursor->prev) {
			if (cursor->type == SEG_MOVETO)
				break;
			cursor = cursor->prev;
		}
		segment->p[0] = cursor->p[0];
		render_line_sel(canim, path, anchor, segment->p[0]);
	} else if (segment->type == SEG_SMOOTH_QUADRATIC) {
		t_point ctrl;
		if (segment->prev->type == SEG_QUADRATIC || segment->prev->type == SEG_SMOOTH_QUADRATIC)
			ctrl = reflect_point(segment->prev->p[0], anchor);
		else if (segment->prev->type == SEG_CUBIC || segment->prev->type == SEG_SMOOTH_CUBIC)
			ctrl = reflect_point(segment->prev->p[2], anchor);
		else
			ctrl = anchor;
		points[count++] = anchor;
		quadratic_adaptive(anchor, ctrl, segment->p[0], tol, points, &count);
		for (int i = 0; i < count - 1; i++)
			render_line_sel(canim, path, points[i], points[i + 1]);
	} else if (segment->type == SEG_SMOOTH_CUBIC) {
		t_point ctrl1;
		if (segment->prev->type == SEG_CUBIC || segment->prev->type == SEG_SMOOTH_CUBIC)
			ctrl1 = reflect_point(segment->prev->p[1], anchor);
		else if (segment->prev->type == SEG_QUADRATIC || segment->prev->type == SEG_SMOOTH_QUADRATIC)
			ctrl1 = reflect_point(segment->prev->p[0], anchor);
		else
			ctrl1 = anchor;
		t_point ctrl2 = segment->p[0];
		t_point end = segment->p[1];
		points[count++] = anchor;
		cubic_adaptive(anchor, ctrl1, ctrl2, end, tol, points, &count);
		for (int i = 0; i < count - 1; i++)
			render_line_sel(canim, path, points[i], points[i + 1]);
	}
	(void)path;
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
	path->stroke_width = 10;
	path->stroke = color_from_hex(0x00ffff00);

	return path;
}

/*void render_path(t_canim *canim) {*/
/*	t_path	  *path;*/
/*	t_segment *segment;*/
/**/
/*	path = simple_path();*/
/*	segment = path->head;*/
/*	while (segment) {*/
/*		render_segment(canim, path, segment);*/
/*		segment = segment->next;*/
/*	}*/
/*path = simple_path2();*/
/*segment = path->head;*/
/*while (segment) {*/
/*	render_segment(canim, path, segment);*/
/*	segment = segment->next;*/
/*}*/
/*path = create_circle((t_point){WIDTH / 2, HEIGHT / 2}, 200);*/
/*segment = path->head;*/
/*while (segment) {*/
/*	render_segment(canim, path, segment);*/
/*	segment = segment->next;*/
/*}*/
/*}*/

t_shape *create_shape(t_path *path) {
	t_shape *shape = malloc(sizeof(t_shape));
	if (!shape)
		return NULL;
	shape->next = NULL;
	shape->path = path;
	return shape;
}

t_shape *add_shape(t_shape *head, t_shape *new) {
	t_shape *mem = head;
	if (!head)
		return new;
	while (head->next)
		head = head->next;
	head->next = new;
	return mem;
}

void render_path(t_canim *canim) {
	/*t_shape *shape = malloc(sizeof(t_shape));*/

	/*shape->path = simple_path();*/
	/*shape->next = NULL;*/

	t_shape *shape = NULL;
	shape = add_shape(shape, create_shape(simple_path()));
	shape = add_shape(shape, create_shape(simple_path2()));
	shape = add_shape(shape, create_shape(simple_path2()));
	shape = add_shape(shape, create_shape(create_circle((t_point){(float)WIDTH / 2, (float)HEIGHT / 2}, 200)));

	while (shape) {
		t_path	  *path = shape->path;
		t_segment *segment = path->head;
		while (segment) {
			render_segment(canim, path, segment);
			segment = segment->next;
		}
		shape = shape->next;
	}
}
