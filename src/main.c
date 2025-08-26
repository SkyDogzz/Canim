#include "canim.h"


static void init_canim(t_canim *canim) {
	canim->frame = 0;
	canim->last_frame = glfwGetTime();
	canim->start_time = glfwGetTime();
	canim->shape = NULL;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s scene.lua\n", argv[0]);
		return 1;
	}

	t_canim canim;
	init_canim(&canim);

	lua_State *L = luaL_newstate();
	register_lua(&canim, L, argv);
	// render
	mainloop(&canim);

	lua_close(L);
	return 0;
}
