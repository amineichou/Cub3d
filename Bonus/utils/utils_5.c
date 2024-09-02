/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:42:40 by moichou           #+#    #+#             */
/*   Updated: 2024/09/02 18:05:28 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
	check if the door is valid
	returns 1 if it is, -1 if it is not
*/
int	is_valid_door(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_door(map[y][x]))
			{
				if (is_usless_door(map, x, y))
					return (ft_printerror("invalid map, useless door.\n"), -1);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/*
	check if the door is useless
	usless door is a door that is not connected to any wall
	or surrounded by walls
	returns true if it is usless, false if it is not
*/
bool	is_usless_door(char **map, int x, int y)
{
	if (map[y][x] == 'D')
	{
		if (y == 0 || !map[y + 1] || x == 0 || !map[y][x + 1])
			return (true);
		if (map[y - 1][x] == '1' && map[y + 1][x] == '1'
			&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
			return (true);
		if (map[y - 1][x] != '1' && map[y + 1][x] != '1'
			&& map[y][x - 1] != '1' && map[y][x + 1] != '1')
			return (true);
		if ((map[y - 1][x] == '1' && map[y + 1][x] != '1')
			|| (map[y][x - 1] == '1' && map[y][x + 1] != '1'))
			return (true);
		if ((map[y - 1][x] != '1' && map[y + 1][x] == '1')
			|| (map[y][x - 1] != '1' && map[y][x + 1] == '1'))
			return (true);
	}
	return (false);
}

/*
	check if the map has only valid chars
*/
int	non_valid_chars(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_char(map[y][x]))
				return (ft_printerror(MAP_ERR_CHARS), -1);
			x++;
		}
		y++;
	}
	return (1);
}

/*
	atoi but returns color values only
*/
int	ft_atoi_color(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		if (res > 255 || sign == -1)
			return (ft_printerror("invalid color value\n"),
				g_malloc(0, FREE), exit(1), -1);
		i++;
	}
	return (res * sign);
}

/*
    remove the spaces and tabs from the start
    and the end of a string
*/
char	*ft_trim_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	j = ft_strlen(str) - 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (ft_isspace(str[j]))
		j--;
	j = ft_strlen(str) - j - 1;
	res = ft_strldup(str + i, (ft_strlen(str) - i - j));
	if (!res)
		return (ft_printerror(MALLOC_ERR), NULL);
	return (res);
}
