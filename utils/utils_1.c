/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:00:33 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 12:57:26 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_printerror(char *msg)
{
	int	i;

	i = 0;
	write (2, "cub3d error : ", 15);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}