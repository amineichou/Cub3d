/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:50:30 by skarim            #+#    #+#             */
/*   Updated: 2024/08/01 09:05:26 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	clear_image(mlx_image_t* image)
{
	unsigned int	y;
	unsigned int	x;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
		{
            mlx_put_pixel(image, x, y, ft_pixel(0, 0, 0, 0));
		}
	}
}

void    draw_3d(t_cub *cub)
{
    int     i;
    float   wall_strip_height;
    float   distance_project_plane;
    float   correct_distance;
    t_point top_point;
    t_point bottom_point;
    int     color;

    i = -1;
    while (++i < NUM_RAYS)
    {
        correct_distance = cub->rays[i].distance * cos(cub->player.angle - cub->rays[i].ray_angle);
        distance_project_plane = (WIDTH / 2) / tan(FOV / 2);
        wall_strip_height = (TILE_SIZE / correct_distance) * distance_project_plane;
        top_point.x = i;
        top_point.y = (HEIGHT / 2) - (wall_strip_height / 2);
        bottom_point.x = i;
        bottom_point.y = (HEIGHT / 2) + (wall_strip_height / 2);
        if (top_point.y < 0)
            top_point.y = 0;
        if (bottom_point.y > HEIGHT)
            bottom_point.y = HEIGHT;
        color = cub->rays[i].hit_vertical ? ft_pixel(128, 0, 0, 255) : ft_pixel(160, 82, 45, 255);
        draw_line(top_point, bottom_point, cub, color);
        float ceil = -1;
        while (++ceil < top_point.y)
            mlx_put_pixel(cub->image, i, ceil, ft_pixel(173, 216, 235, 255));
        float floor = bottom_point.y - 1;
        while (++floor < HEIGHT)
            mlx_put_pixel(cub->image, i, floor, ft_pixel(222, 184, 135, 255));
    }
}