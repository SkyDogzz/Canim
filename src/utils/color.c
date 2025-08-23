#include "canim.h"

t_rgb color_from_hex(int hex) {
	t_rgb color;
	color.r = (hex >> 16) & 0xff;
	color.g = (hex >> 8) & 0xff;
	color.b = hex & 0xff;
	return color;
}

t_rgb color_from_all(uint8_t r, uint8_t g, uint8_t b) {
	t_rgb color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}

t_rgba colora_from_hex(int hex) {
	t_rgba colora;
	colora.r = (hex >> 16) & 0xff;
	colora.g = (hex >> 8) & 0xff;
	colora.b = hex & 0xff;
	colora.a = (hex >> 24) & 0xff;
	return colora;
}

t_rgba colora_from_all(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	t_rgba colora;
	colora.r = r;
	colora.g = g;
	colora.b = b;
	colora.a = a;
	return colora;
}

t_rgba colora_from_color(t_rgb color, uint8_t a) {
	t_rgba colora;
	colora.r = color.r;
	colora.g = color.g;
	colora.b = color.b;
	colora.a = a;
	return colora;
}
