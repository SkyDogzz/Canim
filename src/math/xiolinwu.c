#include "canim.h"

// helper: plot pixel with brightness (0.0f = dark, 1.0f = full white)

static void wu_plot(t_canim *canim, int x, int y, float brightness) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;

	int			  idx = (y * WIDTH + x) * 3;
	unsigned char old = canim->pixels[idx];
	unsigned char new = (unsigned char)(brightness * 255.0f);

	if (new > old)
		canim->pixels[idx] = new;
	canim->pixels[idx + 1] = canim->pixels[idx];
	canim->pixels[idx + 2] = canim->pixels[idx];
}

static float rfpart(float x) {
	return 1.0f - (x - floorf(x));
}
static float fpart(float x) {
	return x - floorf(x);
}

void render_line_wu(t_canim *canim, t_point p1, t_point p2) {
	float x0 = p1.x, y0 = p1.y;
	float x1 = p2.x, y1 = p2.y;

	int steep = fabsf(y1 - y0) > fabsf(x1 - x0);

	if (steep) {
		float tmp;
		tmp = x0;
		x0 = y0;
		y0 = tmp;
		tmp = x1;
		x1 = y1;
		y1 = tmp;
	}

	if (x0 > x1) {
		float tmp;
		tmp = x0;
		x0 = x1;
		x1 = tmp;
		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}

	float dx = x1 - x0;
	float dy = y1 - y0;
	float gradient = dx == 0.0f ? 1.0f : dy / dx;

	// first endpoint
	int	  xend = (int)roundf(x0);
	float yend = y0 + gradient * (xend - x0);
	float xgap = rfpart(x0 + 0.5f);
	int	  xpxl1 = xend;
	int	  ypxl1 = (int)floorf(yend);

	if (steep) {
		wu_plot(canim, ypxl1, xpxl1, rfpart(yend) * xgap);
		wu_plot(canim, ypxl1 + 1, xpxl1, fpart(yend) * xgap);
	} else {
		wu_plot(canim, xpxl1, ypxl1, rfpart(yend) * xgap);
		wu_plot(canim, xpxl1, ypxl1 + 1, fpart(yend) * xgap);
	}

	float intery = yend + gradient;

	// second endpoint
	xend = (int)roundf(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = fpart(x1 + 0.5f);
	int xpxl2 = xend;
	int ypxl2 = (int)floorf(yend);

	if (steep) {
		wu_plot(canim, ypxl2, xpxl2, rfpart(yend) * xgap);
		wu_plot(canim, ypxl2 + 1, xpxl2, fpart(yend) * xgap);
	} else {
		wu_plot(canim, xpxl2, ypxl2, rfpart(yend) * xgap);
		wu_plot(canim, xpxl2, ypxl2 + 1, fpart(yend) * xgap);
	}

	// main loop
	if (steep) {
		for (int x = xpxl1 + 1; x < xpxl2; x++) {
			wu_plot(canim, (int)floorf(intery), x, rfpart(intery));
			wu_plot(canim, (int)floorf(intery) + 1, x, fpart(intery));
			intery += gradient;
		}
	} else {
		for (int x = xpxl1 + 1; x < xpxl2; x++) {
			wu_plot(canim, x, (int)floorf(intery), rfpart(intery));
			wu_plot(canim, x, (int)floorf(intery) + 1, fpart(intery));
			intery += gradient;
		}
	}
}
