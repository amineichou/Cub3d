/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:57:14 by moichou           #+#    #+#             */
/*   Updated: 2024/09/02 22:10:24 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_mlx_init(t_cub *cub)
{
	if (!(cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
	{
		perror(mlx_strerror(mlx_errno));
		return (exit(1), 1);
	}
	if (!(cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(cub->mlx);
		perror(mlx_strerror(mlx_errno));
		return (exit(1), 1);
	}
    return (0);
}
