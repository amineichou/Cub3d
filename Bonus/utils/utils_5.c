/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:42:40 by moichou           #+#    #+#             */
/*   Updated: 2024/09/01 13:49:35 by moichou          ###   ########.fr       */
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
