/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:57:14 by moichou           #+#    #+#             */
/*   Updated: 2024/09/03 12:30:39 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_mlx_init(t_cub *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!cub->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		return (exit(1), 1);
	}
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image)
	{
		mlx_close_window(cub->mlx);
		perror(mlx_strerror(mlx_errno));
		return (exit(1), 1);
	}
	return (0);
}

void	ft_init_cub(t_cub *cub, t_config *game_config)
{
	ft_mlx_init(cub);
	cub->map = game_config->map;
	init_floor_ceil_color(cub, game_config);
	cub->mapx = game_config->mapx;
	cub->mapy = game_config->mapy;
	if (!ft_get_player_postion(&cub->player, cub->map, 0, 0))
		return ;
	ft_load_images(cub, game_config);
	ft_init_player(&(cub->player));
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		perror(mlx_strerror(mlx_errno));
		return ;
	}
	cub->shooting_active = 0;
}
