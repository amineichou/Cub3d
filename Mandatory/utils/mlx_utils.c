/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:43:08 by moichou           #+#    #+#             */
/*   Updated: 2024/09/03 14:48:49 by moichou          ###   ########.fr       */
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
