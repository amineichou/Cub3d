MAN_NAME = cub3D
BONUS_NAME = cub3D_bonus
MAN_SRC = Mandatory/main.c \
		Mandatory/drawing/draw_tools.c Mandatory/drawing/draw.c \
		Mandatory/player/player.c \
		Mandatory/raycasting/horizontal_raycasting.c Mandatory/raycasting/raycasting.c \
		Mandatory/raycasting/vertical_raycasting.c \
		Mandatory/garbage_collector/garbage_collector.c Mandatory/parser/parser.c Mandatory/parser/parse_map.c \
		Mandatory/parser/get_config.c Mandatory/parser/get_next_line.c Mandatory/parser/make_map.c \
		Mandatory/utils/utils_1.c Mandatory/utils/utils_2.c Mandatory/utils/utils_3.c \
		Mandatory/utils/ft_split.c Mandatory/utils/mlx_utils.c\
		Mandatory/utils/utils_4.c Mandatory/parser/parse_args.c

BONUS_SRC = Bonus/main.c \
		Bonus/drawing/draw_tools.c Bonus/drawing/draw.c \
		Bonus/player/player.c \
		Bonus/raycasting/horizontal_raycasting.c Bonus/raycasting/raycasting.c \
		Bonus/raycasting/vertical_raycasting.c \
		Bonus/garbage_collector/garbage_collector.c Bonus/parser/parser.c Bonus/parser/parse_map.c \
		Bonus/parser/get_config.c Bonus/parser/get_next_line.c Bonus/parser/make_map.c \
		Bonus/utils/utils_1.c Bonus/utils/utils_2.c Bonus/utils/utils_3.c \
		Bonus/utils/utils_4.c Bonus/utils/utils_5.c Bonus/utils/ft_split.c \
		Bonus/utils/mlx_utils.c Bonus/parser/parse_args.c \
		Bonus/minimap/minimap.c Bonus/minimap/minimap_utils.c Bonus/animation/pov.c \

CC = cc
FLAGS = -O3 -Wall -Wextra -Werror
MAN_OBJ = $(MAN_SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(MAN_NAME)

%.o: %.c Mandatory/headers/cub.h
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c Bonus/headers/cub.h
	$(CC) $(FLAGS) -c $< -o $@

$(MAN_NAME): $(MAN_OBJ)
	$(CC) $(FLAGS) $(MAN_OBJ) -o $(MAN_NAME) MLX42/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(FLAGS) $(BONUS_OBJ) -o $(BONUS_NAME) MLX42/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"

clean:
	rm -rf $(MAN_OBJ) $(BONUS_OBJ)

fclean:	clean
	rm -rf $(MAN_NAME) $(BONUS_NAME)

re:	clean all

.Phony:	clean