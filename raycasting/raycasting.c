/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:32:05 by skarim            #+#    #+#             */
/*   Updated: 2024/08/02 11:19:56 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
Initialize a ray with given angle and ID
*/
void	ft_init_ray(t_cub *cub, float ray_angle, int ray_id)
{
    cub->rays[ray_id].ray_angle = ft_periodic(ray_angle);
    cub->rays[ray_id].wall_hitx = 0;
    cub->rays[ray_id].wall_hity = 0;
    cub->rays[ray_id].distance = 0;
    cub->rays[ray_id].hit_horizontal = 0;
    cub->rays[ray_id].hit_vertical = 0;
    cub->rays[ray_id].up = cub->rays[ray_id].ray_angle > 0 && cub->rays[ray_id].ray_angle < M_PI;
    cub->rays[ray_id].down = !cub->rays[ray_id].up;
    cub->rays[ray_id].right = cub->rays[ray_id].ray_angle > 3 * M_PI / 2 || cub->rays[ray_id].ray_angle < M_PI / 2;
    cub->rays[ray_id].left = !cub->rays[ray_id].right;
}

/*
Check if a given pixel position is a wall
*/
int     is_wall(t_cub *cub, float xpixel, float ypixel)
{
    int newx;
    int newy;

    newx = floor(xpixel / TILE_SIZE);
    newy = floor(ypixel / TILE_SIZE);
	if (newx < 0 || newx >= MAPX || newy < 0 || newy >= MAPY)
        return 0;
    return (cub->map[newy][newx] == '1');
}

/*
Compare horizontal and vertical ray collisions and update ray data
*/
void	ft_check(t_cub *cub, t_ray vertical_ray, t_ray horizontal_ray, int ray_id)
{
	float hor_distance;
    float ver_distance;

    hor_distance = horizontal_ray.hit_horizontal ? (cub->player.xpixel - horizontal_ray.wall_hitx) * (cub->player.xpixel - horizontal_ray.wall_hitx) + (cub->player.ypixel - horizontal_ray.wall_hity) * (cub->player.ypixel - horizontal_ray.wall_hity) : INT_MAX;
    ver_distance = vertical_ray.hit_vertical ? (cub->player.xpixel - vertical_ray.wall_hitx) * (cub->player.xpixel - vertical_ray.wall_hitx) + (cub->player.ypixel - vertical_ray.wall_hity) * (cub->player.ypixel - vertical_ray.wall_hity) : INT_MAX;
	if (hor_distance < ver_distance)
	{
		cub->rays[ray_id].wall_hitx = horizontal_ray.wall_hitx;
		cub->rays[ray_id].wall_hity = horizontal_ray.wall_hity;
		cub->rays[ray_id].hit_vertical = 0;
        cub->rays[ray_id].hit_horizontal = 1;
		cub->rays[ray_id].distance = sqrt(hor_distance);
	}
	else
	{
		cub->rays[ray_id].wall_hitx = vertical_ray.wall_hitx;
		cub->rays[ray_id].wall_hity = vertical_ray.wall_hity;
		cub->rays[ray_id].hit_vertical = 1;
        cub->rays[ray_id].hit_horizontal = 0;
		cub->rays[ray_id].distance = sqrt(ver_distance);
	}
}

/*
Cast rays for the player's field of view
*/
void    cast_rays(t_cub *cub)
{
    int     ray_id;
    float   ray_angle;
    int     i;

    ray_id = 0;
    i = 0;
    ray_angle = cub->player.angle + (FOV / 2);
    while (i < NUM_RAYS)
    {
        ft_init_ray(cub, ray_angle, ray_id);
		ft_check(cub, check_vertical(cub, ray_id), check_horizontal(cub, ray_id), ray_id);
        ray_angle -= FOV / NUM_RAYS;
        i++;
        ray_id++;
    }
}
