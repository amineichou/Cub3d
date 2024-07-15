/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:52:35 by moichou           #+#    #+#             */
/*   Updated: 2024/07/15 15:30:38 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <limits.h>

# define BUFFER_SIZE 500

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

// define errors
# define OPEN_ERR "can't open the configuration file\n"
# define EXT_ERR "invalid file, make sure the filename format is (file.cub)\n"
# define MALLOC_ERR "can't allocat this region, malloc error\n"
// garbage collector
void	*g_malloc(size_t size, t_g_malloc mode);

// utils
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_printerror(char *msg);
char	*ft_strrchr(char *s, int c);
char	*ft_strjoin(char *first, char *second);
int		ft_strsearch(char *str, char c);
char	*ft_strdup(char *str);
char	*ft_strldup(char *s1, int lenght);
int		ft_isspace(char c);
int		ft_isemptystr(char *str);
char	*ft_trim_spaces(char *str);
char	*get_line(char *file_content, int count);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	**ft_divide_str(char *str);
int		is_valid_map_char(char c);
int		is_player(char c);

// read_all_file
char	*get_next_line(int fd);

// parser
int			parse_map(char **map);
int			parser(int ac, char **filename);
t_config	*make_config(char *filename);
char		**make_map(char *map_str, int s_row, int s_clm);

#endif