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
	path->stroke_opacity = 255;
	path->animation = NULL;
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
	/*path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_points(1, (t_point){200, 200})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_pointss(1, (t_point[]){{400, 400}})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_points(1, (t_point){400, 400})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_points(1, (t_point){400, 400})));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(100, 100, 400, 200, 400, 100)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(162, 14, 204.88,*/
	/*314.159, 42.42, 8.590)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(300, 200)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(12, 55.6, 225, 450, 111, 512)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(100, 100)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(100, 300)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(200, 300)));*/
	/*path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));*/
	/*path = add_seg_to_path(path, create_segment(SEG_LINETO, create_point(200, 0)));*/
	path = add_seg_to_path(path, create_segment(SEG_MOVETO, create_point(0, 400)));
	path = add_seg_to_path(path, create_segment(SEG_QUADRATIC, create_2_points(0, 0, 400, 0)));
	path = add_seg_to_path(path, create_segment(SEG_CUBIC, create_3_points(100, 100, 400, 300, 600, 400)));
	path = add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
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
	t_point *pts = create_point(moveto[0].x, moveto[0].y);
	add_seg_to_path(path, create_segment(SEG_MOVETO, pts));
	free(pts);

	for (int i = 0; i < 4; i++) {
		t_point *pts = create_3_points(controls[i][0].x, controls[i][0].y, controls[i][1].x, controls[i][1].y,
									   moveto[(i + 1) % 4].x, moveto[(i + 1) % 4].y);
		add_seg_to_path(path, create_segment(SEG_CUBIC, pts));
		free(pts);
	}
	add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
	return path;
}

void rotate_points(t_point *pts, int count, t_point center, float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	for (int i = 0; i < count; i++) {
		float x = pts[i].x - center.x;
		float y = pts[i].y - center.y;

		float xr = x * c - y * s;
		float yr = x * s + y * c;

		pts[i].x = xr + center.x;
		pts[i].y = yr + center.y;
	}
}

t_path *create_square(t_point c, float r, float fi) {
	t_point points[4] = {
		{c.x - r / 2, c.y - r / 2}, {c.x + r / 2, c.y - r / 2}, {c.x + r / 2, c.y + r / 2}, {c.x - r / 2, c.y + r / 2}};

	rotate_points(points, 4, c, fi);

	t_path *path = create_path();
	t_point *p = create_point(points[0].x, points[0].y);
	add_seg_to_path(path, create_segment(SEG_MOVETO, p));
	free(p);
	for (int i = 1; i < 4; i++) {
		p = create_point(points[i].x, points[i].y);
		add_seg_to_path(path, create_segment(SEG_LINETO, p));
		free(p);
	}
	add_seg_to_path(path, create_segment(SEG_CLOSE, NULL));
	return path;
}

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
	while (head && head->next)
		head = head->next;
	head->next = new;
	return mem;
}

static t_point apply_rotation(t_point p, t_point center, float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	float x = p.x - center.x;
	float y = p.y - center.y;

	float xr = x * c - y * s;
	float yr = x * s + y * c;

	return (t_point){xr + center.x, yr + center.y};
}

t_point compute_offset(t_animate *anim);
float	compute_rotation(t_animate *anim);
void	render_path(t_canim *canim, t_path *path, float progress) {
	   // clamp progress [0,1]
	   if (progress < 0)
		   progress = 0;
	   if (progress > 1)
		   progress = 1;

	   // compute offset (translation)
	   t_point offset = compute_offset(path->animation);
	   float   rotation = compute_rotation(path->animation);

	   // choose line renderer
	   void (*render_line_sel)(t_canim *, t_path *, t_point, t_point);
	   render_line_sel = LINE_WU ? &render_line_wu : &render_line_bresen;

	   // collect all points
	   t_point points[10000];
	   int	   count = 0;

	   t_segment *seg = path->head;
	   while (seg) {
		   if (seg->prev) {
			   t_point anchor;
			   if (seg->prev->type == SEG_CUBIC)
				   anchor = seg->prev->p[2];
			   else if (seg->prev->type == SEG_QUADRATIC || seg->prev->type == SEG_SMOOTH_CUBIC)
				   anchor = seg->prev->p[1];
			   else
				   anchor = seg->prev->p[0];

			   if (seg->type == SEG_CUBIC) {
				   points[count++] = anchor;
				   cubic_adaptive(anchor, seg->p[0], seg->p[1], seg->p[2], 0.01f, points, &count);
			   } else if (seg->type == SEG_QUADRATIC) {
				   points[count++] = anchor;
				   quadratic_adaptive(anchor, seg->p[0], seg->p[1], 0.01f, points, &count);
			   } else if (seg->type == SEG_LINETO) {
				   points[count++] = anchor;
				   points[count++] = seg->p[0];
			   } else if (seg->type == SEG_CLOSE) {
				   t_segment *cursor = seg;
				   while (cursor->prev && cursor->type != SEG_MOVETO)
					   cursor = cursor->prev;
				   points[count++] = anchor;
				   points[count++] = cursor->p[0];
			   }
		   }
		   seg = seg->next;
	   }

	   if (count < 2)
		   return;
	   t_point centroid = {0, 0};
	   for (int i = 0; i < count; i++) {
		   centroid.x += points[i].x;
		   centroid.y += points[i].y;
	   }
	   centroid.x /= count;
	   centroid.y /= count;
	   int	 total_lines = count - 1;
	   float progress_lines = progress * total_lines;
	   int	 full = (int)progress_lines;
	   float frac = progress_lines - full;

	   // draw fully completed lines

	   for (int i = 0; i < full; i++) {
		   t_point p1 = apply_rotation(points[i], centroid, rotation);
		   t_point p2 = apply_rotation(points[i + 1], centroid, rotation);

		   p1.x += offset.x;
		   p1.y += offset.y;
		   p2.x += offset.x;
		   p2.y += offset.y;

		   render_line_sel(canim, path, p1, p2);
	   }

	   // draw partial of the next line
	   if (full < total_lines) {
		   t_point a = {points[full].x + offset.x, points[full].y + offset.y};
		   t_point b = {points[full + 1].x + offset.x, points[full + 1].y + offset.y};
		   t_point mid = {a.x + (b.x - a.x) * frac, a.y + (b.y - a.y) * frac};
		   render_line_sel(canim, path, a, mid);
	   }
}

static float compute_progress(t_animate *anim) {
	double now = glfwGetTime();

	if (!anim)
		return 1;

	double elapsed = now - anim->start;

	while (anim) {
		if (anim->type == CREATE) {
			double progress;
			if (anim->repeat == ONCE) {
				progress = elapsed / anim->duration;
			} else if (anim->repeat == INFINITE) {
				double cycle = anim->duration;
				double pos = fmod(elapsed, cycle);
				progress = pos / anim->duration;
			} else {
				progress = 1;
			}
			if (progress < 0)
				progress = 0;
			if (progress > 1)
				progress = 1;
			if (anim->timing == LINEAR) {
				return progress;
			} else if (anim->timing == EASE_IN) {
				return progress * progress;
			} else if (anim->timing == EASE_OUT) {
				return 1 - (1 - progress) * (1 - progress);
			} else if (anim->timing == EASE_IN_OUT) {
				if (progress < 0.5) {
					return 2 * progress * progress;
				} else {
					return 1 - pow(-2 * progress + 2, 2) / 2;
				}
			}
		}
		anim = anim->next;
	}
	return 1;
}

t_point compute_offset(t_animate *anim) {
	if (!anim)
		return (t_point){0, 0};

	double now = glfwGetTime();

	if (now < anim->start)
		return (t_point){0, 0};

	double elapsed = now - anim->start;

	double	   total_duration = 0;
	t_animate *tmp = anim;
	while (tmp) {
		if (tmp->type == TRANSLATE)
			total_duration += tmp->duration;
		tmp = tmp->next;
	}

	if (anim->repeat == INFINITE && total_duration > 0) {
		elapsed = fmod(elapsed, total_duration);
	}

	t_point current = {0, 0};
	tmp = anim;

	while (tmp) {
		if (tmp->type == TRANSLATE) {
			if (elapsed < tmp->duration) {
				double progress = elapsed / tmp->duration;
				if (tmp->timing == EASE_IN) {
					progress = progress * progress;
				} else if (tmp->timing == EASE_OUT) {
					progress = 1 - (1 - progress) * (1 - progress);
				} else if (tmp->timing == EASE_IN_OUT) {
					if (progress < 0.5)
						progress = 2 * progress * progress;
					else
						progress = 1 - pow(-2 * progress + 2, 2) / 2;
				}
				current.x += tmp->from.x + (tmp->to.x - tmp->from.x) * progress;
				current.y += tmp->from.y + (tmp->to.y - tmp->from.y) * progress;
				return current;
			} else {
				current.x += tmp->to.x;
				current.y += tmp->to.y;
				elapsed -= tmp->duration;
			}
		}
		tmp = tmp->next;
	}

	return current;
}

float compute_rotation(t_animate *anim) {
	if (!anim)
		return 0;

	double now = glfwGetTime();

	if (now < anim->start)
		return 0;

	double elapsed = now - anim->start;

	double	   total_duration = 0;
	t_animate *tmp = anim;
	while (tmp) {
		if (tmp->type == ROTATE)
			total_duration += tmp->duration;
		tmp = tmp->next;
	}

	if (anim->repeat == INFINITE && total_duration > 0) {
		elapsed = fmod(elapsed, total_duration);
	}

	float current = 0;
	tmp = anim;

	while (tmp) {
		if (tmp->type == ROTATE) {
			if (elapsed < tmp->duration) {
				double progress = elapsed / tmp->duration;
				if (tmp->timing == EASE_IN) {
					progress = progress * progress;
				} else if (tmp->timing == EASE_OUT) {
					progress = 1 - (1 - progress) * (1 - progress);
				} else if (tmp->timing == EASE_IN_OUT) {
					if (progress < 0.5)
						progress = 2 * progress * progress;
					else
						progress = 1 - pow(-2 * progress + 2, 2) / 2;
				}
				current += tmp->fromA + (tmp->toA - tmp->fromA) * progress;
				return current;
			} else {
				current += tmp->toA;
				elapsed -= tmp->duration;
			}
		}
		tmp = tmp->next;
	}
	return current;
}

void render_shapes(t_canim *canim) {
	t_shape *shape;

	shape = canim->shape;
	while (shape) {
		t_path *path = shape->path;
		float	progress = compute_progress(path->animation);
		render_path(canim, path, progress);
		shape = shape->next;
	}
}
