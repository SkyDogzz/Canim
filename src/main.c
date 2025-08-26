#include "canim.h"


static void init_canim(t_canim *canim) {
	canim->frame = 0;
	canim->last_frame = glfwGetTime();
	canim->start_time = glfwGetTime();
	canim->shape = NULL;
	memset(canim->pixels, 0, WIDTH * HEIGHT * 4);
}

static void clear_animation(t_animate *animation)
{
	if (animation && animation->next)
		clear_animation(animation->next);
	if (animation)
		free(animation);
}

static void clear_segment(t_segment *segment)
{
	if (segment && segment->next)
		clear_segment(segment->next);
	if (segment)
	{
		free(segment);
	}
}

static void clear_path(t_path *path)
{
	if (path)
	{
		clear_segment(path->head);
		clear_animation(path->animation);
		free(path);
	}
}

static void clear_shape(t_shape *shape)
{
	if (shape && shape->next)
		clear_shape(shape->next);
	if (shape)
	{
		clear_path(shape->path);
		free(shape);
	}
}

static void clear_canim(t_canim *canim)
{
	clear_shape(canim->shape);
	(void) canim;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s scene.lua\n", argv[0]);
        return 1;
    }

    if (!glfwInit()) {
        fprintf(stderr, "Failed to init GLFW\n");
        return 1;
    }

    t_canim canim;
    init_canim(&canim);

    printf("start_time=%f last_frame=%f\n", canim.start_time, canim.last_frame);

    lua_State *L = luaL_newstate();
    register_lua(&canim, L, argv);

    mainloop(&canim);

    lua_close(L);
    clear_canim(&canim);
    glfwTerminate();
    return 0;
}

