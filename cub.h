/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:52:35 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 13:26:47 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>

/* define errors */
# define OPEN_ERR "can't open map file\n"
# define NO_EXT_ERR "invalid file, file has no extension (.cub)\n"
# define EXT_ERR "invalid extension for map filename (.cub)\n"

/* utils */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_printerror(char *msg);

/* parser */

int		map_vaidator(char *filename);
int		parser(int ac, char **filename);

#endif