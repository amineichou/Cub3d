/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:52:35 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 16:54:20 by moichou          ###   ########.fr       */
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

/* define errors */
# define OPEN_ERR "can't open the configuration file\n"
# define NO_EXT_ERR "invalid file, file has no extension (.cub)\n"
# define EXT_ERR "invalid extension for map filename (.cub)\n"

// garbage collector
void	*g_malloc(size_t size, t_g_malloc mode);

/* utils */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_printerror(char *msg);
char	*ft_strrchr(char *s, int c);
char	*ft_strjoin(char *first, char *second);
int		ft_strsearch(char *str, char c);
char	*ft_strdup(char *str);

/* get_next_line */
char	*read_all_file(int fd);

/* parser */
int		map_vaidator(char *filename);
int		parser(int ac, char **filename);

#endif