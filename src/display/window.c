#include "canim.h"

void set_pixel(t_canim *canim, int x, int y, unsigned char r, unsigned char g,
			   unsigned char b) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	int idx = (y * WIDTH + x) * 3;
	canim->pixels[idx + 0] = r;
	canim->pixels[idx + 1] = g;
	canim->pixels[idx + 2] = b;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
				  int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	(void)mods;
	(void)action;
	(void)scancode;
}

void *init_window(const int width, const int height, const char *title) {
	GLFWwindow *window;
	if (!glfwInit()) {
		printf("Failed to init glfw\n");
		return NULL;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_CANIM_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_CANIM_MINOR);
	if (!(window = glfwCreateWindow(width, height, title, NULL, NULL))) {
		printf("Failed to create window\n");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	// glfwSwapInterval(0);
	glfwSetKeyCallback(window, key_callback);
	return window;
}

void create_square(t_canim *canim, float flateness) {
	double cx = (float)WIDTH / 2;
	double cy = (float)HEIGHT / 2;
	double r = 200;
	float t = 1.0 - (flateness / 100.0f);
	double k = 0.5522847498 * t;
	double c = k * r;


	int step = 500;
	t_point cube[4][4];
	// TOP → RIGHT
	cube[0][0] = (t_point){cx, cy - r};     // Start
	cube[0][1] = (t_point){cx + c, cy - r}; // Control 1
	cube[0][2] = (t_point){cx + r, cy - c}; // Control 2
	cube[0][3] = (t_point){cx + r, cy};     // End

	// RIGHT → BOTTOM
	cube[1][0] = (t_point){cx + r, cy};     // Start
	cube[1][1] = (t_point){cx + r, cy + c}; // Control 1
	cube[1][2] = (t_point){cx + c, cy + r}; // Control 2
	cube[1][3] = (t_point){cx, cy + r};     // End

	// BOTTOM → LEFT
	cube[2][0] = (t_point){cx, cy + r};     // Start
	cube[2][1] = (t_point){cx - c, cy + r}; // Control 1
	cube[2][2] = (t_point){cx - r, cy + c}; // Control 2
	cube[2][3] = (t_point){cx - r, cy};     // End

	// LEFT → TOP
	cube[3][0] = (t_point){cx - r, cy};     // Start
	cube[3][1] = (t_point){cx - r, cy - c}; // Control 1
	cube[3][2] = (t_point){cx - c, cy - r}; // Control 2
	cube[3][3] = (t_point){cx, cy - r};

	t_point arc[4][step];
	cubic_bezier(arc[0], cube[0][0], cube[0][1], cube[0][2], cube[0][3], step);
	cubic_bezier(arc[1], cube[1][0], cube[1][1], cube[1][2], cube[1][3], step);
	cubic_bezier(arc[2], cube[2][0], cube[2][1], cube[2][2], cube[2][3], step);
	cubic_bezier(arc[3], cube[3][0], cube[3][1], cube[3][2], cube[3][3], step);

	for (int i = 0; i < step; i++) {
		set_pixel(canim, arc[0][i].x, arc[0][i].y, 255, 255, 255);
		set_pixel(canim, arc[1][i].x, arc[1][i].y, 255, 255, 255);
		set_pixel(canim, arc[2][i].x, arc[2][i].y, 255, 255, 255);
		set_pixel(canim, arc[3][i].x, arc[3][i].y, 255, 255, 255);
	}
}

void mainloop(t_canim *canim) {
	canim->window = init_window(720, 480, "Display");
	if (!canim->window)
		return;
	glGenTextures(1, &canim->tex);
	glBindTexture(GL_TEXTURE_2D, canim->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB,
			  GL_UNSIGNED_BYTE, canim->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// t_point a, b, c;
	// a.x = 0;
	// a.y = 4;
	// b.x = 0;
	// b.y = 0;
	// c.x = 4;
	// c.y = 0;
	// int goal = 4;
	//
	// int step = 1000;
	// t_point points[step];

	int goal = 100;
	float flat = 0;
	while (!glfwWindowShouldClose(canim->window)) {
		memset(canim->pixels, 0, WIDTH * HEIGHT * 3);
		glClear(GL_COLOR_BUFFER_BIT);

		// if (goal > 0 && b.x < goal) {
		// 	b.x += 0.01;
		// 	b.y += 0.01;
		// } else {
		// 	b.x -= 0.01;
		// 	b.y -= 0.01;
		// }
		// if (b.x >= 4 && goal == 4)
		// 	goal = 0;
		// else if (b.x <= 0 && goal == 0)
		// 	goal = 4;
		// quadratic_bezier(points, a, b, c, step);
		// for (int i = 0; i < step; i++) {
		// 	set_pixel(canim, points[i].x * 100, points[i].y * 100, 255, 0, 255);
		// }
		create_square(canim, flat);
		if (goal > flat)
			flat += 2;
		else if (goal < flat)
			flat -= 2;
		if (flat == goal) {
			if (goal == 100)
				goal = 0;
			else
				goal = 100;
		}

		glBindTexture(GL_TEXTURE_2D, canim->tex);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGB,
				  GL_UNSIGNED_BYTE, canim->pixels);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);
		glTexCoord2f(1, 0);
		glVertex2f(1, -1);
		glTexCoord2f(1, 1);
		glVertex2f(1, 1);
		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glfwSwapBuffers(canim->window);
		glfwPollEvents();
		double now = glfwGetTime();
		if (DEBUG) {
			printf("%ld frame rendered in %.2fms\n", canim->frame++,
		  (now - canim->last_frame) * 1000);
			printf("Elapsed time = %.2fs\n", now - canim->start_time);
		}
		canim->last_frame = now;
	}
	glfwDestroyWindow(canim->window);
	glfwTerminate();
}
