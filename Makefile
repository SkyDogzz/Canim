NAME := canim
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wunused-function -MMD -MP -ofast
LDFLAGS := -lGL -lglfw
INCLUDES = -I ./include

all: $(NAME)

ifdef DEBUG
CFLAGS += -g3
CFLAGS += -D DEBUG=true
endif
ifdef FSAN
CFLAGS += -fsanitize=address
endif

SRC_PATH := src/
OBJ_PATH := obj/

DISPLAY_SRC		:= window.c

SRC := main.c \
	   $(addprefix display/, $(DISPLAY_SRC)) \

SRCS := $(addprefix $(SRC_PATH), $(SRC))
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_DIRS := $(sort $(dir $(OBJS)))

-include $(OBJS:.o=.d)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)
		
re: fclean all
