/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:43:08 by moichou           #+#    #+#             */
/*   Updated: 2024/09/05 12:05:28 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int	ft_mlx_init(t_cub *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!cub->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		return (exit(1), 1);
	}
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image)
	{
		mlx_close_window(cub->mlx);
		perror(mlx_strerror(mlx_errno));
		return (exit(1), 1);
	}
	return (0);
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
	return (0);
}
