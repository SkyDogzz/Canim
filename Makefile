NAME := canim
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wunused-function -MMD -MP -Ofast
LDFLAGS := -lGL -lglfw
INCLUDES := -I ./include

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
	   math/math.c

SRCS := $(addprefix $(SRC_PATH), $(SRC))
OBJS := $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

-include $(wildcard $(OBJS:.o=.d))

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
