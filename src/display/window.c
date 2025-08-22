#include "canim.h"

void set_pixel(t_canim *canim, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	int idx = (y * WIDTH + x) * 3;
	canim->pixels[idx + 0] = r;
	canim->pixels[idx + 1] = g;
	canim->pixels[idx + 2] = b;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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
	glfwSwapInterval(0);
	glfwSetKeyCallback(window, key_callback);
	return window;
}

void mainloop(t_canim *canim) {
	canim->window = init_window(WIDTH, HEIGHT, "Display");
	if (!canim->window)
		return;
	glGenTextures(1, &canim->tex);
	glBindTexture(GL_TEXTURE_2D, canim->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, canim->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (!glfwWindowShouldClose(canim->window)) {
		memset(canim->pixels, 0, WIDTH * HEIGHT * 3);
		glClear(GL_COLOR_BUFFER_BIT);
		render_path(canim);

		glBindTexture(GL_TEXTURE_2D, canim->tex);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, canim->pixels);
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
			printf("%ld frame rendered in %.2fms\n", canim->frame++, (now - canim->last_frame) * 1000);
			printf("Elapsed time = %.2fs\n", now - canim->start_time);
			printf("Framerate = %.2f fps\n", 1.0 / (now - canim->last_frame));
		}
		canim->last_frame = now;
	}
	glfwDestroyWindow(canim->window);
	glfwTerminate();
}
