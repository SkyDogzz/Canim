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
	float t = 0;
	float x = 1.0 / step;

	while (step) {
		t_point a = point_add(q, point_mult(point_sub(p, q), 1 - t));
		t_point b = point_add(q, point_mult(point_sub(s, q), t));
		points[step - 1] = point_add(a, point_mult(point_sub(b, a), t));
		step--;
		t += x;
	}
}

void cubic_bezier(t_point *points, t_point p1, t_point p2, t_point p3, t_point p4, int step) {
	float t = 0;
	float x = 1.0 / step;

	while (step) {
		points[step - 1].x =
			pow(1 - t, 3) * p1.x + 3 * t * pow(1 - t, 2) * p2.x + 3 * pow(t, 2) * (1 - t) * p3.x + pow(t, 3) * p4.x;
		points[step - 1].y =
			pow(1 - t, 3) * p1.y + 3 * t * pow(1 - t, 2) * p2.y + 3 * pow(t, 2) * (1 - t) * p3.y + pow(t, 3) * p4.y;
		step--;
		t += x;
	}
}

#define MAX_POINTS 1000

void quadratic_adaptive(t_point p, t_point q, t_point r, float tol, t_point *points, int *count) {
	if (*count >= MAX_POINTS)
		return;

	// distance of q from line (p,r)
	float dx = r.x - p.x;
	float dy = r.y - p.y;
	float d = fabsf((q.x - p.x) * dy - (q.y - p.y) * dx) / sqrtf(dx * dx + dy * dy);

	if (d <= tol || *count >= MAX_POINTS - 1) {
		// flat enough → add endpoint
		points[(*count)++] = r;
	} else {
		// split at t=0.5
		t_point p1 = {(p.x + q.x) * 0.5f, (p.y + q.y) * 0.5f};
		t_point p2 = {(q.x + r.x) * 0.5f, (q.y + r.y) * 0.5f};
		t_point mid = {(p1.x + p2.x) * 0.5f, (p1.y + p2.y) * 0.5f};

		quadratic_adaptive(p, p1, mid, tol, points, count);
		quadratic_adaptive(mid, p2, r, tol, points, count);
	}
}

void cubic_adaptive(t_point p1, t_point p2, t_point p3, t_point p4, float tol, t_point *points, int *count) {
	if (*count >= MAX_POINTS)
		return;

	// distance of p2 and p3 from line (p1,p4)
	float dx = p4.x - p1.x;
	float dy = p4.y - p1.y;
	float d1 = fabsf((p2.x - p1.x) * dy - (p2.y - p1.y) * dx);
	float d2 = fabsf((p3.x - p1.x) * dy - (p3.y - p1.y) * dx);
	float d = fmaxf(d1, d2) / sqrtf(dx * dx + dy * dy);

	if (d <= tol || *count >= MAX_POINTS - 1) {
		points[(*count)++] = p4;
	} else {
		// de Casteljau subdivision
		t_point p12 = {(p1.x + p2.x) * 0.5f, (p1.y + p2.y) * 0.5f};
		t_point p23 = {(p2.x + p3.x) * 0.5f, (p2.y + p3.y) * 0.5f};
		t_point p34 = {(p3.x + p4.x) * 0.5f, (p3.y + p4.y) * 0.5f};

		t_point p123 = {(p12.x + p23.x) * 0.5f, (p12.y + p23.y) * 0.5f};
		t_point p234 = {(p23.x + p34.x) * 0.5f, (p23.y + p34.y) * 0.5f};

		t_point mid = {(p123.x + p234.x) * 0.5f, (p123.y + p234.y) * 0.5f};

		cubic_adaptive(p1, p12, p123, mid, tol, points, count);
		cubic_adaptive(mid, p234, p34, p4, tol, points, count);
	}
}
