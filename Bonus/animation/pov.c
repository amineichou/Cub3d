/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:38:38 by moichou           #+#    #+#             */
/*   Updated: 2024/08/07 17:22:05 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

#define FRAMES 49


mlx_image_t	*ft_get_single_image(t_cub *cub, char *pathname)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(pathname);
	if (!texture)
	{
		ft_printerror("texture file error to open\n");
		exit(1);
	}
	image = mlx_texture_to_image(cub->mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

/*
	load images
*/
mlx_image_t	*load_normal_image(t_cub *cub, int image_number)
{
	mlx_image_t *image;
	char	*pathname;

	pathname = ft_strjoin("animation/normal/", ft_itoa(image_number));
	pathname = ft_strjoin(pathname, ".png");
	image = ft_get_single_image(cub, pathname);
	if (!image)
	{
		ft_printerror("image error normal frames\n");
		exit(1);
	}
	return (image);
}


void	ft_render_infinite(t_cub *cub, mlx_image_t *loaded_images[FRAMES])
{
	int i;

	i = 0;
	while (1)
	{
		mlx_image_to_window(cub->mlx, loaded_images[i], 0, 0);
		usleep(4000);
		i++;
		if (i == FRAMES)
			i = 0;
	}
}

void	ft_pov(t_cub *cub, t_actions action)
{
	mlx_image_t *image;

	if (action == NORMAL)
	{
		image = ft_get_single_image(cub, "animation/normal.png");
		mlx_image_to_window(cub->mlx, image, WIDTH / 6, HEIGHT / 3);
	}
}