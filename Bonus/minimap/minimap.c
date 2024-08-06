/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:54:27 by skarim            #+#    #+#             */
/*   Updated: 2024/08/06 21:01:22 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_minimap(t_cub *cub, int radius)
{
	int	x;
	int	y;
	int	color;
	int	xposition;
	int	yposition;

	y = -radius - 1;
	while (++y < radius)
	{
		x = -radius - 1;
		while (++x < radius)
		{
			if (sqrt(x * x + y * y) < radius)
			{
				xposition = floor((cub->player.xpixel + x / MINIMAP_SCALE_FACTOR) / TILE_SIZE);
				yposition = floor((cub->player.ypixel + y / MINIMAP_SCALE_FACTOR) / TILE_SIZE);
				color = ft_pixel(0, 0, 0, 255);
				if (xposition < MAPX && xposition >= 0 && yposition < MAPY && yposition >= 0)
					if (cub->map[yposition][xposition] == '1')
						color = ft_pixel(255, 255, 255, 255);
				mlx_put_pixel(cub->image, (radius + x + MINIMAP_PAD), (radius + y + MINIMAP_PAD), color);
			}
		}
	}
}

void	draw_player(t_cub *cub, int radius)
{
	int	x;
	int	y;

	x = -cub->player.radius * MINIMAP_SCALE_FACTOR;
	while (x < cub->player.radius * MINIMAP_SCALE_FACTOR)
	{
		y = -cub->player.radius * MINIMAP_SCALE_FACTOR;
		while (y < cub->player.radius * MINIMAP_SCALE_FACTOR)
		{
			if (x * x + y * y < cub->player.radius * cub->player.radius * MINIMAP_SCALE_FACTOR * MINIMAP_SCALE_FACTOR)
			{
				mlx_put_pixel(cub->image, (radius + x + MINIMAP_PAD) , (radius + y + MINIMAP_PAD) , ft_pixel(0, 120, 0, 255));
			}
			y++;
		}
		x++;
	}
}

void    draw_one_ray(t_point start_point, t_point end_point, t_cub *cub)
{
    int     dx;
    int     dy;
    int     steps;
    float   xinc;
    float   yinc;
    float   x;
    float   y;
    int     i;

    dx = end_point.x - start_point.x;
    dy = end_point.y - start_point.y;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    x = start_point.x;
    y = start_point.y;
    i = -1;
    while (++i <= steps)
    {
        plot(round(x), round(y), cub, ft_pixel(255, 0, 0, 100 * exp(-0.0005 * ((x - start_point.x) * (x - start_point.x) + (y - start_point.y) * (y - start_point.y)))));
        x += xinc;
        y += yinc;
    }
}

void	draw_rays(t_cub *cub, int radius)
{
	int			i;
	t_point		start_point;
	t_point		end_point;
	float		ray_angle;
	float		ray_distance;

	start_point.x = radius + MINIMAP_PAD;
	start_point.y = radius + MINIMAP_PAD;
	i = -1;
	while (++i < NUM_RAYS)
	{
		end_point.x = cub->rays[i].wall_hitx - cub->rays[i].right + cub->rays[i].left;
		end_point.y = cub->rays[i].wall_hity + cub->rays[i].up - cub->rays[i].down;
		ray_distance = sqrt(pow(cub->rays[i].wall_hitx - cub->player.xpixel, 2) +
                            pow(cub->rays[i].wall_hity - cub->player.ypixel, 2));
		float intersection_distance = radius / MINIMAP_SCALE_FACTOR;
		if (ray_distance > intersection_distance)
		{
			ray_angle = atan2(cub->rays[i].wall_hity - cub->player.ypixel, cub->rays[i].wall_hitx - cub->player.xpixel);
			end_point.x = cub->player.xpixel + intersection_distance * cos(ray_angle);
			end_point.y = cub->player.ypixel + intersection_distance * sin(ray_angle);
		}
		end_point.x = (end_point.x - cub->player.xpixel - cub->rays[i].right + cub->rays[i].left) * MINIMAP_SCALE_FACTOR + start_point.x;
		end_point.y = (end_point.y - cub->player.ypixel + cub->rays[i].up - cub->rays[i].down) * MINIMAP_SCALE_FACTOR + start_point.y;
		draw_one_ray(start_point, end_point, cub);
	}
}

void draw_minimap_border(t_cub *cub, int radius, int border_width)
{
    int	x;
	int	y;
	int	outer_radius;
	float distance;
	
	outer_radius = radius + border_width;
	y = -outer_radius - 1;
    while (++y < outer_radius)
	{
        x = -outer_radius - 1;
        while (++x < outer_radius)
		{
			distance = sqrt(x * x + y * y);
            if (distance < outer_radius && distance > radius)
			{
				mlx_put_pixel(cub->image, (outer_radius + x + MINIMAP_PAD - border_width),
					(outer_radius + y + MINIMAP_PAD - border_width), ft_pixel(200, 230, 170, 115));
            }
        }
    }
}

void    ft_minimap(t_cub *cub)
{
    int	radius;
	
	radius = 4 * TILE_SIZE * MINIMAP_SCALE_FACTOR;
	draw_minimap(cub, radius);
    draw_player(cub, radius);
	draw_rays(cub, radius);
	draw_minimap_border(cub, radius, 5);
}
