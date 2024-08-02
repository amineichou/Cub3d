/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:14:04 by skarim            #+#    #+#             */
/*   Updated: 2024/08/02 11:23:10 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
/*
Initialize vertical raycasting data
*/
t_data_rays init_vertical_data(t_cub *cub, int ray_id)
{
    t_data_rays data;
    
    data.xintercept = floor(cub->player.xpixel / TILE_SIZE) * TILE_SIZE;
    data.xintercept += cub->rays[ray_id].left ? 0 : TILE_SIZE;
    data.yintercept = cub->player.ypixel + (cub->player.xpixel - data.xintercept) * tan(cub->rays[ray_id].ray_angle);
    data.xstep = TILE_SIZE;
    data.xstep *= cub->rays[ray_id].left ? -1 : 1;
    data.ystep = TILE_SIZE * tan(cub->rays[ray_id].ray_angle);
    data.ystep *= (cub->rays[ray_id].up && data.ystep > 0) ? -1 : 1;
    data.ystep *= (cub->rays[ray_id].down && data.ystep < 0) ? -1 : 1;
    return (data);
}

/*
Check for vertical ray collisions
*/
t_ray   check_vertical_collisions(t_cub *cub, int ray_id, t_data_rays data)
{
    t_ray vertical_ray = {0};
    float next_vert_hitx;
    float next_vert_hity;

    next_vert_hitx = data.xintercept;
    next_vert_hity = data.yintercept;
    while (next_vert_hitx >= 0 && next_vert_hitx <= WIDTH && next_vert_hity >= 0 && next_vert_hity <= HEIGHT)
    {
        if (is_wall(cub, next_vert_hitx - cub->rays[ray_id].left, next_vert_hity))
        {
            vertical_ray.wall_hitx = next_vert_hitx;
            vertical_ray.wall_hity = next_vert_hity;
            vertical_ray.hit_vertical = 1;
            vertical_ray.hit_horizontal = 0;
            break;
        }
        else
        {
            next_vert_hitx += data.xstep;
            next_vert_hity += data.ystep;
        }
    }
    return (vertical_ray);
}

/*
Perform vertical raycasting for a ray
*/
t_ray   check_vertical(t_cub *cub, int ray_id)
{
    t_data_rays data;

    data = init_vertical_data(cub, ray_id);
    return (check_vertical_collisions(cub, ray_id, data));
}
