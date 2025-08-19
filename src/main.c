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

/*t_path *create_circle(t_point c, float r);*/
/**/
/*static int lua_create_circle(lua_State *L) {*/
/*    float cx = luaL_checknumber(L, 1);  // arg1*/
/*    float cy = luaL_checknumber(L, 2);  // arg2*/
/*    float r  = luaL_checknumber(L, 3);  // arg3*/
/**/
/*    t_path *path = create_circle((t_point){cx, cy}, r);*/
/**/
/*    // store pointer as light userdata so Lua can pass it back*/
/*    lua_pushlightuserdata(L, path);*/
/*    return 1; // returning 1 value*/
/*}*/
/**/
/*int main(void) {*/
/*	lua_State *L = luaL_newstate();*/
/*	luaL_openlibs(L);*/
/**/
/*	// Register your functions*/
/*	lua_register(L, "create_circle", lua_create_circle);*/
/**/
/*	// Run a Lua script*/
/*	if (luaL_dofile(L, "scene.lua") != LUA_OK) {*/
/*		fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));*/
/*		return 1;*/
/*	}*/
/**/
/*	lua_close(L);*/
/*	return 0;*/
/*}*/
