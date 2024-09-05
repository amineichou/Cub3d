NAME = cub3d
SRC = main.c \
		drawing/draw_tools.c drawing/draw.c \
		player/player.c \
		raycasting/horizontal_raycasting.c raycasting/raycasting.c raycasting/vertical_raycasting.c \
		garbage_collector/garbage_collector.c parser/parser.c parser/parse_map.c \
		parser/get_config.c parser/get_next_line.c parser/make_map.c \
		utils/utils_1.c utils/utils_2.c utils/utils_3.c utils/utils_4.c utils/utils_5.c utils/ft_split.c \
		utils/mlx_utils.c parser/parse_args.c \
		minimap/minimap.c minimap/minimap_utils.c animation/pov.c \

CC = cc
FLAGS = -O3 -Wall -Wextra -Werror -fsanitize=address -g
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c headers/cub.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) MLX42/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"


clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	clean all

.Phony:	clean