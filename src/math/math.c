#include "canim.h"

static t_point point_sub(t_point a, t_point b) {
	t_point ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

static t_point point_mult(t_point a, float b) {
	t_point ret;
	ret.x = a.x * b;
	ret.y = a.y * b;
	return ret;
}

static t_point point_add(t_point a, t_point b) {
	t_point ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return ret;
}

/*
 * p define the first control point (the start)
 * q define the center control point (the one the curve will try to reach)
 * s define the second control point (the end)
 */
void quadratic_bezier(t_point *points, t_point p, t_point q, t_point s, int step) {
	float	t = 0;
	float	x = 1.0 / step;

	while (step) {
		t_point a = point_add(q, point_mult(point_sub(p, q), 1 - t));
		t_point b = point_add(q, point_mult(point_sub(s, q), t));
		points[step - 1] = point_add(a, point_mult(point_sub(b, a), t));
		step--;
		t += x;
	}
}
