/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:50:30 by skarim            #+#    #+#             */
/*   Updated: 2024/09/05 11:29:11 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

/*
	** Get the pixel color from the image at the given coordinates.
	4 bytes are used to store the color information of each pixel.
*/
int	mlx_get_pixel(mlx_image_t *image, const uint32_t x, const uint32_t y)
{
	int				index;
	int				r;
	int				g;
	int				b;
	int				a;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return (0);
	index = (y * image->width + x) * 4;
	r = image->pixels[index + 0];
	g = image->pixels[index + 1];
	b = image->pixels[index + 2];
	a = image->pixels[index + 3];
	return (ft_pixel(r, g, b, a));
}

void	draw_ceiling_floor(t_cub *cub, t_point top_point,
					t_point bottom_point, int i)
{
	float	floor;
	float	ceil;

	ceil = -1;
	while (++ceil < top_point.y)
		mlx_put_pixel(cub->image, i, ceil,
			ft_pixel(cub->c[0], cub->c[1], cub->c[2], cub->c[3]));
	floor = bottom_point.y - 1;
	while (++floor < HEIGHT)
		mlx_put_pixel(cub->image, i, floor,
			ft_pixel(cub->f[0], cub->f[1], cub->f[2], cub->f[3]));
}

void	draw_walls(t_cub *cub, t_point top_point, t_point bottom_point, int i)
{
	float	wall_hit_x;
	int		tex_x;
	float	y;
	int		distance_from_top;
	int		tex_y;

	if (cub->rays[i].hit_vertical)
		wall_hit_x = fmod(cub->rays[i].wall_hity, TILE_SIZE);
	else
		wall_hit_x = fmod(cub->rays[i].wall_hitx, TILE_SIZE);
	tex_x = wall_hit_x * (cub->texture->width / TILE_SIZE);
	y = top_point.y;
	while (y < bottom_point.y)
	{
		distance_from_top = y + (cub->wall_strip_height / 2) - (HEIGHT / 2);
		tex_y = distance_from_top * (cub->texture->height
				/ cub->wall_strip_height);
		mlx_put_pixel(cub->image, i, y,
			mlx_get_pixel(cub->texture, tex_x, tex_y));
		y++;
	}
}

void	init_texture_images(t_cub *cub, int i)
{
	if (cub->rays[i].is_door)
		cub->texture = cub->door;
	else
	{
		if (cub->rays[i].hit_vertical)
		{
			if (cub->rays[i].ray_angle < M_PI / 2
				|| cub->rays[i].ray_angle > 3 * M_PI / 2)
				cub->texture = cub->ea;
			else
				cub->texture = cub->we;
		}
		else
		{
			if (cub->rays[i].ray_angle < M_PI)
				cub->texture = cub->no;
			else
				cub->texture = cub->so;
		}
	}
}

/*
	** Draw the 3D representation of the map.
	dpp = distance from the player to the projection plane.
	aka distance project plane
*/
void	draw_3d(t_cub *cub)
{
	int			i;
	float		dpp;
	float		correct_distance;
	t_point		top_point;
	t_point		bottom_point;

	i = -1;
	while (++i < NUM_RAYS)
	{
		correct_distance = cub->rays[i].distance
			* cos(cub->player.angle - cub->rays[i].ray_angle);
		dpp = (WIDTH / 2) / tan(FOV / 2);
		cub->wall_strip_height = (TILE_SIZE / correct_distance) * dpp;
		top_point.x = i;
		top_point.y = (HEIGHT / 2) - (cub->wall_strip_height / 2);
		bottom_point.x = i;
		bottom_point.y = (HEIGHT / 2) + (cub->wall_strip_height / 2);
		if (top_point.y < 0)
			top_point.y = 0;
		if (bottom_point.y > HEIGHT)
			bottom_point.y = HEIGHT;
		init_texture_images(cub, i);
		draw_walls(cub, top_point, bottom_point, i);
		draw_ceiling_floor(cub, top_point, bottom_point, i);
	}
}
