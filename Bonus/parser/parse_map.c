/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:04:30 by moichou           #+#    #+#             */
/*   Updated: 2024/09/05 11:29:43 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

/*
	check if the character is a player or door
*/
bool	is_player_door(char c)
{
	if (is_player(c) || is_door(c))
		return (true);
	return (false);
}

/*
	check if for a (0, player, door) if it is surrounded by walls
	returns 1 if it is, 0 if it is not
*/
int	is_inwall(char **map, int x, int y, t_direction dir)
{
	if (dir == TOP)
	{
		while (y && (map[y][x] == '0' || is_player_door(map[y][x])))
			y--;
	}
	else if (dir == RIGHT)
	{
		while (map[y][x] && (map[y][x] == '0' || is_player_door(map[y][x])))
			x++;
	}
	else if (dir == BOTTOM)
	{
		while (map[y] && map[y + 1]
			&& (map[y][x] == '0' || is_player_door(map[y][x])))
			y++;
	}
	else if (dir == LEFT)
	{
		while (x && (map[y][x] == '0' || is_player_door(map[y][x])))
			x--;
	}
	if (map[y][x] != '1')
		return (0);
	return (1);
}

/*
	check if the map surrounded by walls
	returns 1 if it is, -1 if it is not
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
			if (map[y][x] == '0' || is_player(map[y][x]) || is_door(map[y][x]))
			{
				if (!is_inwall(map, x, y, TOP)
					|| !is_inwall(map, x, y, RIGHT)
					|| !is_inwall(map, x, y, BOTTOM)
					|| !is_inwall(map, x, y, LEFT))
					return (ft_printerror(MAP_ERR_WALL), -1);
			}
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
			if (is_player(map[y][x]))
				player++;
			if (player > 2)
				return (ft_printerror("invalid map, duplicate player.\n"), 1);
			x++;
		}
		y++;
	}
	if (player == 0)
		return (ft_printerror("invalid map, no player.\n"), 1);
	return (0);
}

/*
	checks the map for errors
	returns 1 if the map is valid, -1 if it is not
	all function used prints an error message explaining the error
*/
int	parse_map(char **map)
{
	if (non_valid_chars(map) == -1
		|| wall_surrounded(map) == -1
		|| is_duplicate_player(map)
		|| is_valid_door(map) == -1)
		return (-1);
	return (1);
}
