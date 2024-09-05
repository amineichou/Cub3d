/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:02:49 by skarim            #+#    #+#             */
/*   Updated: 2024/09/05 11:30:55 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

void	draw_one_ray(t_point start_point, t_point end_point, t_cub *cub)
{
	int		steps;
	float	xinc;
	float	yinc;
	float	x;
	float	y;

	if (abs(end_point.x - start_point.x) > abs(end_point.y - start_point.y))
		steps = abs(end_point.x - start_point.x);
	else
		steps = abs(end_point.y - start_point.y);
	xinc = (end_point.x - start_point.x) / (float)steps;
	yinc = (end_point.y - start_point.y) / (float)steps;
	x = start_point.x;
	y = start_point.y;
	while (--steps >= 0)
	{
		plot(round(x), round(y), cub, ft_pixel(255, 0, 0,
				100 * exp(-0.0005 * ((x - start_point.x) * (x - start_point.x)
						+ (y - start_point.y) * (y - start_point.y)))));
		x += xinc;
		y += yinc;
	}
}

void	limit_draw_ray(t_cub *cub, int i, t_point *end_point)
{
	float		ray_angle;

	ray_angle = atan2(cub->rays[i].wall_hity - cub->player.ypixel,
			cub->rays[i].wall_hitx - cub->player.xpixel);
	end_point->x = cub->player.xpixel
		+ MINIMAP_RADIUS / MINIMAP_SCALE_FACTOR * cos(ray_angle);
	end_point->y = cub->player.ypixel
		+ MINIMAP_RADIUS / MINIMAP_SCALE_FACTOR * sin(ray_angle);
}

void	draw_rays(t_cub *cub)
{
	int			i;
	t_point		start_point;
	t_point		end_point;
	float		ray_distance;

	start_point.x = MINIMAP_RADIUS + MINIMAP_PAD;
	start_point.y = MINIMAP_RADIUS + MINIMAP_PAD;
	i = -1;
	while (++i < NUM_RAYS)
	{
		end_point.x = cub->rays[i].wall_hitx
			- cub->rays[i].right + cub->rays[i].left;
		end_point.y = cub->rays[i].wall_hity
			+ cub->rays[i].up - cub->rays[i].down;
		ray_distance = sqrt(pow(cub->rays[i].wall_hitx - cub->player.xpixel, 2)
				+ pow(cub->rays[i].wall_hity - cub->player.ypixel, 2));
		if (ray_distance > MINIMAP_RADIUS / MINIMAP_SCALE_FACTOR)
			limit_draw_ray(cub, i, &end_point);
		end_point.x = (end_point.x - cub->player.xpixel - cub->rays[i].right
				+ cub->rays[i].left) * MINIMAP_SCALE_FACTOR + start_point.x;
		end_point.y = (end_point.y - cub->player.ypixel + cub->rays[i].up
				- cub->rays[i].down) * MINIMAP_SCALE_FACTOR + start_point.y;
		draw_one_ray(start_point, end_point, cub);
	}
}
