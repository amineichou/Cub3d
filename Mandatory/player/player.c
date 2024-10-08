/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:07:25 by skarim            #+#    #+#             */
/*   Updated: 2024/09/05 11:22:57 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

/*
Takes an angle in radians and normalizes it to be within the range [0, 2*PI]
*/
float	ft_periodic(float angle)
{
	while (angle < 0)
		angle += (2 * M_PI);
	while (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/*
Initialize player properties
*/
void	ft_init_player(t_player *player)
{
	player->radius = 7;
	player->turn_speed = 3 * M_PI / 180.0;
	player->walk_speed = 3;
	player->xpixel = player->xposition * TILE_SIZE + TILE_SIZE / 2.0;
	player->ypixel = player->yposition * TILE_SIZE + TILE_SIZE / 2.0;
}

/*
Checks if any part of the circle representing
the player intersects with a wall in the map.
*/
bool	is_player_on_wall(t_cub *cub, float xpixel, float ypixel)
{
	float	rad;
	float	check_x;
	float	check_y;
	t_point	check_point;
	int		angle_step;

	angle_step = 0;
	while (angle_step < 360)
	{
		rad = angle_step * M_PI / 180;
		check_x = xpixel + cub->player.radius * cos(rad);
		check_y = ypixel - cub->player.radius * sin(rad);
		check_point.x = floor(check_x / TILE_SIZE);
		check_point.y = floor(check_y / TILE_SIZE);
		if (cub->map[check_point.y][check_point.x] == '1')
			return (true);
		angle_step++;
	}
	return (false);
}

/*
Updates the player's potential new position based on the keys pressed.
(forward, backward, left, or right).
*/
void	player_move(t_cub *cub, float *new_xpixel, float *new_ypixel)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		*new_xpixel += cub->player.walk_speed * cos(cub->player.angle);
		*new_ypixel -= cub->player.walk_speed * sin(cub->player.angle);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		*new_xpixel -= cub->player.walk_speed * cos(cub->player.angle);
		*new_ypixel += cub->player.walk_speed * sin(cub->player.angle);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		*new_xpixel += cub->player.walk_speed * cos(cub->player.angle + M_PI_2);
		*new_ypixel -= cub->player.walk_speed * sin(cub->player.angle + M_PI_2);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		*new_xpixel += cub->player.walk_speed * cos(cub->player.angle - M_PI_2);
		*new_ypixel -= cub->player.walk_speed * sin(cub->player.angle - M_PI_2);
	}
}

/*
Calculates and updates the player's position and angle based on input.
*/
void	update_player_position(t_cub *cub)
{
	float	new_xpixel;
	float	new_ypixel;

	new_xpixel = cub->player.xpixel;
	new_ypixel = cub->player.ypixel;
	player_move(cub, &new_xpixel, &new_ypixel);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player.angle = ft_periodic(cub->player.angle
				- cub->player.turn_speed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player.angle = ft_periodic(cub->player.angle
				+ cub->player.turn_speed);
	if (!is_player_on_wall(cub, new_xpixel, new_ypixel))
	{
		cub->player.xpixel = new_xpixel;
		cub->player.ypixel = new_ypixel;
		cub->player.xposition = floor(new_xpixel / TILE_SIZE);
		cub->player.yposition = floor(new_ypixel / TILE_SIZE);
	}
}
