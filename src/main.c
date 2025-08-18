#include "canim.h"

static void init_canim(t_canim *canim) {
	canim->frame = 0;
	canim->last_frame = glfwGetTime();
	canim->start_time = glfwGetTime();
}

int main(int argc, char *argv[]) {
	t_canim canim;

	init_canim(&canim);
	if (argc == 1) {
		printf("Usage = %s [filename]\n", argv[0]);
		exit(1);
	}
	mainloop(&canim);
	exit(0);
}
