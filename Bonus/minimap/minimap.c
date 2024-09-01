/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:54:27 by skarim            #+#    #+#             */
/*   Updated: 2024/09/01 13:33:22 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_minimap_pixel(t_cub *cub, int x, int y)
{
	int	xposition;
	int	yposition;
	int	color;

	xposition = floor((cub->player.xpixel
				+ x / MINIMAP_SCALE_FACTOR) / TILE_SIZE);
	yposition = floor((cub->player.ypixel
				+ y / MINIMAP_SCALE_FACTOR) / TILE_SIZE);
	color = ft_pixel(0, 0, 0, 255);
	if (xposition < MAPX && xposition >= 0
		&& yposition < MAPY && yposition >= 0)
	{
		if (cub->map[yposition][xposition] == '1')
			color = ft_pixel(255, 255, 255, 255);
		else if (cub->map[yposition][xposition] == 'D'
				&& (cub->player.xposition != xposition
				|| cub->player.yposition != yposition))
			color = ft_pixel(255, 255, 255, 35);
	}
	mlx_put_pixel(cub->image, (MINIMAP_RADIUS + x + MINIMAP_PAD),
		(MINIMAP_RADIUS + y + MINIMAP_PAD), color);
}

void	draw_minimap(t_cub *cub)
{
	int	x;
	int	y;

	y = -MINIMAP_RADIUS - 1;
	while (++y < MINIMAP_RADIUS)
	{
		x = -MINIMAP_RADIUS - 1;
		while (++x < MINIMAP_RADIUS)
		{
			if (sqrt(x * x + y * y) < MINIMAP_RADIUS)
			{
				draw_minimap_pixel(cub, x, y);
			}
		}
	}
}

void	draw_player(t_cub *cub)
{
	int	x;
	int	y;

	x = -cub->player.radius * MINIMAP_SCALE_FACTOR;
	while (x < cub->player.radius * MINIMAP_SCALE_FACTOR)
	{
		y = -cub->player.radius * MINIMAP_SCALE_FACTOR;
		while (y < cub->player.radius * MINIMAP_SCALE_FACTOR)
		{
			if (x * x + y * y < cub->player.radius * cub->player.radius
				* MINIMAP_SCALE_FACTOR * MINIMAP_SCALE_FACTOR)
			{
				mlx_put_pixel(cub->image, (MINIMAP_RADIUS + x + MINIMAP_PAD),
					(MINIMAP_RADIUS + y + MINIMAP_PAD),
					ft_pixel(0, 120, 0, 255));
			}
			y++;
		}
		x++;
	}
}

void	draw_minimap_border(t_cub *cub, int border_width)
{
	int		x;
	int		y;
	int		outer_radius;
	float	distance;

	outer_radius = MINIMAP_RADIUS + border_width;
	y = -outer_radius - 1;
	while (++y < outer_radius)
	{
		x = -outer_radius - 1;
		while (++x < outer_radius)
		{
			distance = sqrt(x * x + y * y);
			if (distance < outer_radius && distance > MINIMAP_RADIUS)
			{
				mlx_put_pixel(cub->image, (outer_radius + x + MINIMAP_PAD
						- border_width), (outer_radius + y + MINIMAP_PAD
						- border_width), ft_pixel(200, 230, 170, 115));
			}
		}
	}
}

void	ft_minimap(t_cub *cub)
{
	draw_minimap(cub);
	draw_rays(cub);
	draw_player(cub);
	draw_minimap_border(cub, 5);
}
