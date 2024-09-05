/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycasting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:30:44 by skarim            #+#    #+#             */
/*   Updated: 2024/09/05 11:23:03 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

/*
Initialize horizontal raycasting data
*/
t_data_rays	init_horizontal_data(t_cub *cub, int ray_id)
{
	t_data_rays	data;

	data.yintercept = floor(cub->player.ypixel / TILE_SIZE) * TILE_SIZE;
	if (cub->rays[ray_id].up)
		data.yintercept += 0;
	else
		data.yintercept += TILE_SIZE;
	data.xintercept = cub->player.xpixel + (cub->player.ypixel
			- data.yintercept) / tan(cub->rays[ray_id].ray_angle);
	data.ystep = TILE_SIZE;
	if (cub->rays[ray_id].up)
		data.ystep *= -1;
	else
		data.ystep *= 1;
	data.xstep = TILE_SIZE / tan(cub->rays[ray_id].ray_angle);
	if (cub->rays[ray_id].left && data.xstep > 0)
		data.xstep *= -1;
	else
		data.xstep *= 1;
	if (cub->rays[ray_id].right && data.xstep < 0)
		data.xstep *= -1;
	else
		data.xstep *= 1;
	return (data);
}

/*
Check for horizontal ray collisions
*/
t_ray	check_horizontal_collisions(t_cub *cub, int ray_id, t_data_rays data)
{
	t_ray	horizontal_ray;
	float	next_horz_hitx;
	float	next_horz_hity;

	horizontal_ray = (t_ray){0};
	next_horz_hitx = data.xintercept;
	next_horz_hity = data.yintercept;
	while (next_horz_hitx >= 0 && next_horz_hitx <= cub->mapx * TILE_SIZE
		&& next_horz_hity >= 0 && next_horz_hity <= cub->mapy * TILE_SIZE)
	{
		if (is_wall(cub, next_horz_hitx, next_horz_hity - cub->rays[ray_id].up))
		{
			horizontal_ray.wall_hitx = next_horz_hitx;
			horizontal_ray.wall_hity = next_horz_hity;
			horizontal_ray.hit_horizontal = 1;
			horizontal_ray.hit_vertical = 0;
			break ;
		}
		else
		{
			next_horz_hitx += data.xstep;
			next_horz_hity += data.ystep;
		}
	}
	return (horizontal_ray);
}

/*
Perform horizontal raycasting for a ray
*/
t_ray	check_horizontal(t_cub *cub, int ray_id)
{
	t_data_rays	data;

	data = init_horizontal_data(cub, ray_id);
	return (check_horizontal_collisions(cub, ray_id, data));
}
