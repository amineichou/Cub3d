/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:04:30 by moichou           #+#    #+#             */
/*   Updated: 2024/07/13 21:43:10 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_inwall(char **map, int x, int y)
{
	if (!map[y + 1] || (map[y + 1][x] != '1' && map[y + 1][x] != '0'))
		return (0);
	else if (y && map[y - 1][x] != '1' && map[y - 1][x] != '0')
		return (0);
	else if (map[y][x + 1] && map[y][x + 1] != '1' && map[y][x + 1] != '0')
		return (0);
	else if (!x || (map[y][x - 1] != '1' && map[y][x - 1] != '0'))
		return (0);
	return (1);
}

/*
	check if the map surrounded by walls
*/
int	wall_surrounded(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (!is_inwall(map, x, y))
					return (ft_printerror("invalid map, not surrounded by walls\n"), -1);
			}
			x++;
		}
		y++;
	}
	return (1);
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
				return (ft_printerror("invalid map.\n"), -1);
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map(char **map)
{
	if (non_valid_chars(map) == -1 
		|| wall_surrounded(map) == -1)
		return (-1);
	return (1);
}
