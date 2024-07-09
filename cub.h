/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:52:35 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 12:59:13 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <mlx.h>


/* utils */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_printerror(char *msg);

/* parser */

int		parser(int ac, char **filename);

#endif