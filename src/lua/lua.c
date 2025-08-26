#include "canim.h"

int l_circle(lua_State *L) {
	t_luactx *ctx = lua_touserdata(L, lua_upvalueindex(1));

	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	float r = luaL_checknumber(L, 3);

	t_shape *s = create_shape(create_circle((t_point){x, y}, r));
	ctx->canim->shape = add_shape(ctx->canim->shape, s);

	lua_pushlightuserdata(L, s);
	return 1;
}

int l_square(lua_State *L) {
	t_luactx *ctx = lua_touserdata(L, lua_upvalueindex(1));

	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	float r = luaL_checknumber(L, 3);

	float fi = 0;
	if (lua_gettop(L) >= 4)
		fi = luaL_checknumber(L, 4);

	t_shape *s = create_shape(create_square((t_point){x, y}, r, fi));
	ctx->canim->shape = add_shape(ctx->canim->shape, s);

	lua_pushlightuserdata(L, s);
	return 1;
}

int l_set_stroke(lua_State *L) {
	// arg1: shape
	t_shape *shape = (t_shape *)lua_touserdata(L, 1);
	if (!shape)
		return luaL_error(L, "Invalid shape");

	// arg2: color string like "#rrggbb"
	const char	*hexstr = luaL_checkstring(L, 2);
	unsigned int hex = 0;
	if (hexstr[0] == '#')
		sscanf(hexstr + 1, "%x", &hex);
	else
		sscanf(hexstr, "%x", &hex);

	// arg3: stroke width
	int stroke_width = luaL_checkinteger(L, 3);

	// arg4: optional opacity (0–255), default 255
	int opacity = 255;
	if (lua_gettop(L) >= 4)
		opacity = luaL_checkinteger(L, 4);

	// apply to path
	shape->path->stroke = color_from_hex(hex);
	shape->path->stroke_width = stroke_width;
	shape->path->stroke_opacity = opacity;

	return 0;  // no return value
}

int l_animate(lua_State *L) {
	// 1. get the shape
	t_shape *shape = (t_shape *)lua_touserdata(L, 1);
	if (!shape)
		return luaL_error(L, "Invalid shape");

	// 2. get the animation type string
	const char *anim_type = luaL_checkstring(L, 2);

	// 3. get options table
	luaL_checktype(L, 3, LUA_TTABLE);

	// extract common fields
	double start = 0, duration = 1;
	int	   timing = LINEAR, repeat = ONCE;

	lua_getfield(L, 3, "start");
	if (lua_isnumber(L, -1))
		start = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, 3, "duration");
	if (lua_isnumber(L, -1))
		duration = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, 3, "timing");
	if (lua_isstring(L, -1)) {
		const char *t = lua_tostring(L, -1);
		if (!strcmp(t, "linear"))
			timing = LINEAR;
		else if (!strcmp(t, "ease_in"))
			timing = EASE_IN;
		else if (!strcmp(t, "ease_out"))
			timing = EASE_OUT;
		else if (!strcmp(t, "ease_in_out"))
			timing = EASE_IN_OUT;
	}
	lua_pop(L, 1);

	lua_getfield(L, 3, "loop");	 // instead of "repeat"
	if (lua_isstring(L, -1)) {
		const char *r = lua_tostring(L, -1);
		if (!strcmp(r, "once"))
			repeat = ONCE;
		else if (!strcmp(r, "infinite"))
			repeat = INFINITE;
	}
	lua_pop(L, 1);

	// 4. Create animation
	t_animate *anim = NULL;
	if (!strcmp(anim_type, "create")) {
		anim = create_animation(CREATE, start, duration, timing, repeat);
	} else if (!strcmp(anim_type, "translate")) {
		// extract from/to
		t_point from = {0, 0}, to = {0, 0};
		lua_getfield(L, 3, "from");
		if (lua_istable(L, -1)) {
			lua_rawgeti(L, -1, 1);
			from.x = lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			from.y = lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, 3, "to");
		if (lua_istable(L, -1)) {
			lua_rawgeti(L, -1, 1);
			to.x = lua_tonumber(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);
			to.y = lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		anim = create_translate(TRANSLATE, start, duration, timing, repeat, from, to);

	} else if (!strcmp(anim_type, "rotate")) {
		float fromA = 0, toA = 0;

		lua_getfield(L, 3, "fromA");
		if (lua_isnumber(L, -1))
			fromA = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, 3, "toA");
		if (lua_isnumber(L, -1))
			toA = lua_tonumber(L, -1);
		lua_pop(L, 1);

		anim = create_rotation(ROTATE, start, duration, timing, repeat, fromA, toA);
	}

	if (anim) {
		shape->path->animation = add_animation(shape->path->animation, anim);
	}

	return 0;
}

bool register_lua(t_canim *canim, lua_State *L, char *argv[]) {
	luaL_openlibs(L);

	// wrap context
	t_luactx ctx = {.canim = canim};

	// register bindings with ctx as upvalue
	lua_pushlightuserdata(L, &ctx);
	lua_pushcclosure(L, l_circle, 1);
	lua_setglobal(L, "circle");

	lua_pushlightuserdata(L, &ctx);
	lua_pushcclosure(L, l_square, 1);
	lua_setglobal(L, "square");

	lua_pushlightuserdata(L, &ctx);
	lua_pushcclosure(L, l_set_stroke, 1);
	lua_setglobal(L, "set_stroke");

	lua_pushlightuserdata(L, &ctx);
	lua_pushcclosure(L, l_animate, 1);
	lua_setglobal(L, "animate");

	// run the scene file
	if (luaL_dofile(L, argv[1])) {
		fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
		return 1;
	}
	return 0;
}
