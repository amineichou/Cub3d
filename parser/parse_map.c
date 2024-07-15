/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:04:30 by moichou           #+#    #+#             */
/*   Updated: 2024/07/15 15:43:51 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_inwall(char **map, int x, int y, t_direction dir)
{
	if (dir == TOP)
	{
		while (y && map[y][x] == '0')
			y--;
	}
	else if (dir == RIGHT)
	{
		while (map[y][x] && map[y][x] == '0')
			x++;
	}
	else if (dir == BOTTOM)
	{
		while (map[y] && map[y + 1] && map[y][x] == '0')
			y++;
	}
	else if (dir == LEFT)
	{
		while (x && map[y][x] == '0')
			x--;
	}
	if (map[y][x] != '1')
		return (0);
	return (1);
}

/*
	check if the map surrounded by walls
	return (ft_printerror("invalid map, not surrounded by walls\n"), -1);
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
				if (!is_inwall(map, x, y, TOP) || !is_inwall(map, x, y, RIGHT) 
				|| !is_inwall(map, x, y, BOTTOM) || !is_inwall(map, x, y, LEFT))
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
				return (ft_printerror("invalid map, bad charachters in presenting.\n"), -1);
			x++;
		}
		y++;
	}
	return (1);
}

/*
	this function checks if there's a duplicate player
	returns 1 if there's, 0 if there is not
*/
int	is_duplicate_player(char **map)
{
	int	x;
	int	y;
	int	player;

	y = 0;
	player = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				player++;
			if (player > 2)
				return (ft_printerror("invalid map, duplicate player.\n"), 1);
			x++;
		}
		y++;
	}
	return (0);
}

int	parse_map(char **map)
{
	if (non_valid_chars(map) == -1 
		|| wall_surrounded(map) == -1
		|| is_duplicate_player(map))
		return (-1);
	return (1);
}
