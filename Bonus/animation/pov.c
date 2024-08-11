/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:38:38 by moichou           #+#    #+#             */
/*   Updated: 2024/08/11 21:47:53 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

#define FRAMES 49

/*
	load images Please fix the path to the images in ft_get_image
*/
mlx_image_t	**ft_get_frames(t_cub *cub, char *path, int frames)
{
	mlx_image_t **images;
	mlx_image_t *image;
	char		*pathname;
	int			i;

	i = 0;
	images = malloc(sizeof(mlx_image_t *) * (frames + 1));
	while (i < frames)
	{
		pathname = ft_strjoin(path, ft_itoa(i));
		pathname = ft_strjoin(pathname, ".png");
		image = ft_get_image(cub, pathname);
		if (!image)
		{
			ft_printerror("image error normal frames\n");
			exit(1);
		}
		if (!mlx_resize_image(image, WIDTH, HEIGHT))
		{
			ft_printerror("resize error\n");
			exit(1);
		}
		images[i] = image;
		i++;
	}
	images[i] = NULL;
	return (images);
}


void	ft_star_shooting(t_cub *cub)
{
	mlx_image_t		**shooting_frames;
	int 			i;

	shooting_frames = ft_get_frames(cub, " ./animation/shooting/", 12);
	i = 0;
	while (shooting_frames[i])
	{
		mlx_image_to_window(cub->mlx, shooting_frames[i], 0, 0);
		for (int j = 0; j < 10; j++)
			;
		mlx_delete_image(cub->mlx, shooting_frames[i]);
		i++;
	}
}

void	ft_pov(t_cub *cub, t_actions action)
{
	int i;

	i = 0;

	if (action == NORMAL)
	{
		mlx_image_to_window(cub->mlx, cub->pov_normal, 0, 0);
	}
	if (action == SHOOT)
	{
		ft_star_shooting(cub);
		printf("shooting\n");
	}
}