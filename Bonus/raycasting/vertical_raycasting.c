/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:14:04 by skarim            #+#    #+#             */
/*   Updated: 2024/09/05 11:29:29 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

/*
Updates the vertical ray structure after detecting a collision.
*/
void	update_vertical_ray(t_cub *cub, t_ray *vertical_ray, int ray_id)
{
	int	newx;
	int	newy;

	newx = floor((vertical_ray->wall_hitx - cub->rays[ray_id].left)
			/ TILE_SIZE);
	newy = floor(vertical_ray->wall_hity / TILE_SIZE);
	if (newx < 0 || newx >= cub->mapx || newy < 0 || newy >= cub->mapy)
		return ;
	vertical_ray->is_door = 0;
	vertical_ray->hit_horizontal = 0;
	vertical_ray->hit_vertical = 1;
	if (cub->map[newy][newx] == 'D')
		vertical_ray->is_door = 1;
}

/*
Initialize vertical raycasting data
*/
t_data_rays	init_vertical_data(t_cub *cub, int ray_id)
{
	t_data_rays	data;

	data.xintercept = floor(cub->player.xpixel / TILE_SIZE) * TILE_SIZE;
	if (cub->rays[ray_id].left)
		data.xintercept += 0;
	else
		data.xintercept += TILE_SIZE;
	data.yintercept = cub->player.ypixel + (cub->player.xpixel
			- data.xintercept) * tan(cub->rays[ray_id].ray_angle);
	data.xstep = TILE_SIZE;
	if (cub->rays[ray_id].left)
		data.xstep *= -1;
	else
		data.xstep *= 1;
	data.ystep = TILE_SIZE * tan(cub->rays[ray_id].ray_angle);
	if (cub->rays[ray_id].up && data.ystep > 0)
		data.ystep *= -1;
	else
		data.ystep *= 1;
	if (cub->rays[ray_id].down && data.ystep < 0)
		data.ystep *= -1;
	else
		data.ystep *= 1;
	return (data);
}

/*
Check for vertical ray collisions
*/
t_ray	check_vertical_collisions(t_cub *cub, int ray_id, t_data_rays data)
{
	t_ray	vertical_ray;
	float	next_ver_hitx;
	float	next_ver_hity;

	vertical_ray = (t_ray){0};
	next_ver_hitx = data.xintercept;
	next_ver_hity = data.yintercept;
	while (next_ver_hitx >= 0 && next_ver_hitx <= cub->mapx * TILE_SIZE
		&& next_ver_hity >= 0 && next_ver_hity <= cub->mapy * TILE_SIZE)
	{
		if (is_wall(cub, next_ver_hitx - cub->rays[ray_id].left, next_ver_hity))
		{
			vertical_ray.wall_hitx = next_ver_hitx;
			vertical_ray.wall_hity = next_ver_hity;
			update_vertical_ray(cub, &vertical_ray, ray_id);
			break ;
		}
		else
		{
			next_ver_hitx += data.xstep;
			next_ver_hity += data.ystep;
		}
	}
	return (vertical_ray);
}

/*
Perform vertical raycasting for a ray
*/
t_ray	check_vertical(t_cub *cub, int ray_id)
{
	t_data_rays	data;

	data = init_vertical_data(cub, ray_id);
	return (check_vertical_collisions(cub, ray_id, data));
}
