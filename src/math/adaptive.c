#include "canim.h"

void quadratic_adaptive(t_point p, t_point q, t_point r, float tol, t_point *points, int *count) {
	if (*count >= MAX_POINTS)
		return;

	float dx = r.x - p.x;
	float dy = r.y - p.y;
	float d = fabsf((q.x - p.x) * dy - (q.y - p.y) * dx) / sqrtf(dx * dx + dy * dy);

	if (d <= tol || *count >= MAX_POINTS - 1) {
		points[(*count)++] = r;
	} else {
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

	float dx = p4.x - p1.x;
	float dy = p4.y - p1.y;
	float d1 = fabsf((p2.x - p1.x) * dy - (p2.y - p1.y) * dx);
	float d2 = fabsf((p3.x - p1.x) * dy - (p3.y - p1.y) * dx);
	float d = fmaxf(d1, d2) / sqrtf(dx * dx + dy * dy);

	if (d <= tol || *count >= MAX_POINTS - 1) {
		points[(*count)++] = p4;
	} else {
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
