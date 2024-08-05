NAME = cub3d
SRC = main.c \
		drawing/draw_tools.c drawing/draw.c \
		player/player.c \
		raycasting/horizontal_raycasting.c raycasting/raycasting.c raycasting/vertical_raycasting.c \
		garbage_collector.c parser/parser.c parser/parse_map.c \
		parser/get_config.c parser/get_next_line.c parser/make_map.c \
		utils/utils_1.c utils/utils_2.c utils/utils_3.c utils/ft_split.c \
		utils/utils_4.c
CC = cc
FLAGS =  -fsanitize=address -g#-Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c cub.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) libmlx42.a -Iinclude -lglfw -L"/Users/moichou/.brew/opt/glfw/lib"


clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	clean all

.Phony:	clean