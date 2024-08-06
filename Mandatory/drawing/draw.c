/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:50:30 by skarim            #+#    #+#             */
/*   Updated: 2024/08/05 22:43:54 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
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

int mlx_get_pixel(mlx_image_t *image, int x, int y) {
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) {
        return 0;
    }

    int bytes_per_pixel = 4;
    int index = (y * image->width + x) * bytes_per_pixel;

    unsigned char *pixel_data = (unsigned char *)image->pixels;

    int r = pixel_data[index + 0];
    int g = pixel_data[index + 1];
    int b = pixel_data[index + 2];
    int a = pixel_data[index + 3];

    return ft_pixel(r, g, b, a);
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
        // draw_line(top_point, bottom_point, cub, color);
        // get xoffset and yoffeset
        // get_offset(cub, i);
        // scale
        // draw_column_from_texture
        // Select the correct texture based on the ray hit direction
        mlx_image_t *texture;
        if (cub->rays[i].hit_vertical) {
            if (cub->rays[i].ray_angle < M_PI / 2 || cub->rays[i].ray_angle > 3 * M_PI / 2) {
                texture = cub->ea; // East texture
            } else {
                texture = cub->we; // West texture
            }
        } else {
            if (cub->rays[i].ray_angle < M_PI) {
                texture = cub->no; // North texture
            } else {
                texture = cub->so; // South texture
            }
        }

        float wall_hit_x;
        if (cub->rays[i].hit_vertical)
            wall_hit_x = fmod(cub->rays[i].wall_hity, TILE_SIZE);
        else
            wall_hit_x = fmod(cub->rays[i].wall_hitx, TILE_SIZE);

        int tex_x = wall_hit_x * ((float)texture->width / TILE_SIZE);

        // Draw the wall strip
        float y = top_point.y;
        while (y < bottom_point.y) {
            int distance_from_top = y + (wall_strip_height / 2) - (HEIGHT / 2);
            int tex_y = distance_from_top * ((float)texture->height / wall_strip_height);
            int tex_color = mlx_get_pixel(texture, tex_x, tex_y);

            mlx_put_pixel(cub->image, i, y, tex_color);
            y++;
        }
        float ceil = -1;
        while (++ceil < top_point.y)
            mlx_put_pixel(cub->image, i, ceil, ft_pixel(20, 1, 55, 255));
        float floor = bottom_point.y - 1;
        while (++floor < HEIGHT)
            mlx_put_pixel(cub->image, i, floor, ft_pixel(16, 16, 33, 255));
    }
}