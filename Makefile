NAME = cub3d
SRC = main.c garbage_collector.c parser/parser.c parser/check_map.c \
		parser/get_config.c parser/get_next_line.c \
		utils/utils_1.c utils/utils_2.c utils/utils_3.c utils/ft_split.c
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
MLX_LINKER_API = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_LIB = -Imlx
MATH_LIB = -lm
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(MATH_LIB) $(OBJ) -o $(NAME)

%.o: %.c cub.h
	$(CC) $(FLAGS) $(MLX_LIB) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean all

.Phony: clean