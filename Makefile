NAME := canim
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wunused-function -MMD -MP -Ofast
LDFLAGS := -lGL -lglfw -lm -ldl
INCLUDES := -I ./include -I ./lua-5.4.7/src

ifdef DEBUG
	CFLAGS += -g3
	CFLAGS += -D DEBUG=true
endif

ifdef FSAN
	CFLAGS += -fsanitize=address
endif

SRC_PATH := src/
OBJ_PATH := obj/

SRC := main.c \
	   path/create.c \
	   display/window.c \
	   math/adaptive.c \
	   math/bresenham.c \
	   math/xiolinwu.c

SRCS := $(addprefix $(SRC_PATH), $(SRC))
OBJS := $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

LUA_VERSION := 5.4.7
LUA_DIR := lua-$(LUA_VERSION)
LUA_TAR := $(LUA_DIR).tar.gz
LUA_URL := https://www.lua.org/ftp/$(LUA_TAR)
LUA_LIB := $(LUA_DIR)/src/liblua.a

all: $(NAME)

$(LUA_TAR):
	curl -R -O $(LUA_URL)

$(LUA_DIR): $(LUA_TAR)
	tar zxf $(LUA_TAR)

$(LUA_LIB): $(LUA_DIR)
	$(MAKE) -C $(LUA_DIR)/src liblua.a
	rm -r $(LUA_TAR)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(LUA_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LUA_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LUA_LIB) $(LDFLAGS) -o $@

-include $(wildcard $(OBJS:.o=.d))

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LUA_DIR)/src clean || true

fclean: clean
	rm -f $(NAME)
	rm -rf $(LUA_DIR) $(LUA_TAR)

re: fclean all

.PHONY: all clean fclean re

