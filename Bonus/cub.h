/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:52:35 by moichou           #+#    #+#             */
/*   Updated: 2024/09/02 17:00:04 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <float.h> 
# include "MLX42.h"


# define BUFFER_SIZE 500
# define WIDTH 1080
# define HEIGHT 720
# define TILE_SIZE 64
# define FOV 60 * (M_PI / 180)
# define NUM_RAYS WIDTH
# define MINIMAP_SCALE_FACTOR 0.4
# define MINIMAP_PAD 13
# define MINIMAP_RADIUS 4 * TILE_SIZE * MINIMAP_SCALE_FACTOR

int MAPX;
int	MAPY;

typedef struct s_point
{
    int x;
    int y;
}   t_point;

typedef struct s_player
{
    float xposition;
    float yposition;
    float xpixel;
    float ypixel;
    float radius;
    float walk_speed;
    float turn_speed;
    float angle;
}   t_player;

typedef struct s_ray
{
    float   ray_angle;
    float   wall_hitx;
    float   wall_hity;
    float   distance;
    int     hit_vertical;
	int		hit_horizontal;
    int     is_door;
    int     up;
    int     down;
    int     left;
    int     right;
}   t_ray;


typedef struct s_cub
{
	mlx_t*			mlx;
	mlx_image_t*	image;
	t_player		player;
	t_ray			rays[WIDTH];
	char			**map;
	int*			color_buffer;
	mlx_image_t		*no;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*ea;
	mlx_image_t		*door;
	mlx_image_t		*pov_normal;
	mlx_image_t		**shooting_frames;
	mlx_image_t		*texture;
	bool			shooting_active;
	int				shooting_duration;
	int				sfc;
	float			wall_strip_height;
	int				f[4];
	int				c[4];
}	t_cub;

typedef struct s_data_rays
{
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;
}   t_data_rays;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**f;
	char	**c;
	char	**map;
}	t_config;

typedef struct s_garbage
{
	void				*allocated;
	struct s_garbage	*next;
}	t_garbage;

typedef enum s_g_malloc
{
	ALLOCATE,
	FREE,
}	t_g_malloc;

typedef enum s_direction
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
}	t_direction;


typedef enum s_actions
{
	NORMAL,
	RELOAD,
	SHOOT,
	JUMP,
}	t_actions;

// define errors
# define OPEN_ERR "can't open the configuration file\n"
# define EXT_ERR "invalid file, make sure the filename format is (file.cub)\n"
# define MALLOC_ERR "can't allocat this region, malloc error\n"
# define MAP_ERR "invalid map. newlines in/after map\n"
# define MAP_ERR_WALL "invalid map, not surrounded by walls\n"
# define MAP_ERR_CHARS "invalid map, bad charachters in presenting.\n"
# define PARSE_ERR "no valid arguments\n"

// main
void		ft_load_images(t_cub *cub, t_config *game_config);

// garbage collector
void		*g_malloc(size_t size, t_g_malloc mode);

// utils
int			ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);
void		ft_printerror(char *msg);
char		*ft_strrchr(char *s, int c);
char		*ft_strjoin(char *first, char *second);
int			ft_strsearch(char *str, char c);
char		*ft_strdup(char *str);
char		*ft_strldup(char *s1, int lenght);
int			ft_isspace(char c);
int			ft_isemptystr(char *str);
char		*ft_trim_spaces(char *str);
char		*get_line(char *file_content, int count);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		**ft_split(char const *s, char c);
char		**ft_divide_str(char *str);
int			is_valid_map_char(char c);
int			is_player(char c);
bool		is_door(char c);
char		*ft_itoa(int n);
int			ft_get_player_postion(t_player *player, char **map, int x, int y);
int			is_valid_door(char **map);
bool		is_usless_door(char **map, int x, int y);
int			non_valid_chars(char **map);
int			ft_atoi_color(const char *str);

// read_all_file
char		*get_next_line(int fd);

// parser
int			parse_map(char **map);
t_config	*parser(int ac, char **filename);
t_config	*make_config(char *filename);
char		**make_map(char *map_str, int s_row, int s_clm);

// raycasting
t_ray		check_horizontal(t_cub *cub, int ray_id);
t_ray		check_vertical(t_cub *cub, int ray_id);
float		ft_periodic(float angle);
void		cast_rays(t_cub *cub);
int			is_wall(t_cub *cub, float xpixel, float ypixel);
int			is_px_door(t_cub *cub, float xpixel, float ypixel);

// player
void		update_player_position(t_cub* cub);
void		ft_init_player(t_player* player);

// drawing
int			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		plot(int x, int y, t_cub *cub, int color);
void		draw_line(t_point start_point, t_point end_point, t_cub *cub, int color);
void		clear_image(mlx_image_t* image);
void		draw_3d(t_cub *cub);
void    	ft_minimap(t_cub *cub);
mlx_image_t	*ft_get_image(t_cub *cub, char *pathname);
void		draw_rays(t_cub *cub);


// animation
mlx_image_t	**ft_get_frames(t_cub *cub, char *path, int frames);
void		ft_pov(void *arg);

#endif