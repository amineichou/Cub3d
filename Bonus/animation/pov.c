/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:38:38 by moichou           #+#    #+#             */
/*   Updated: 2024/08/20 20:08:09 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
		images[i] = image;
		i++;
	}
	images[i] = NULL;
	return (images);
}

void ft_update_shooting(t_cub *cub)
{
	static int i;
    if (cub->shooting_active == 0)
        return;
	
	if (i)
	{
		mlx_resize_image(cub->shooting_frames[cub->shooting_active], WIDTH, HEIGHT);
		mlx_image_to_window(cub->mlx, cub->shooting_frames[cub->shooting_active], 0, 0);
		i = 0;
	}
	if (cub->shooting_duration > 5)
	{
		mlx_delete_image(cub->mlx, cub->shooting_frames[cub->shooting_active]);
		cub->shooting_duration = 0;
		cub->shooting_active += 1;
		if (cub->shooting_active >= 7)
		{
			mlx_delete_image(cub->mlx, cub->shooting_frames[cub->shooting_active]);
			cub->pov_normal = ft_get_image(cub, "../animation/shooting/6.png");
			mlx_resize_image(cub->pov_normal, WIDTH, HEIGHT);
			cub->shooting_active = 0;
			mlx_image_to_window(cub->mlx, cub->pov_normal, 0, 0);
			return ;
		}
		mlx_resize_image(cub->shooting_frames[cub->shooting_active], WIDTH, HEIGHT);
		mlx_image_to_window(cub->mlx, cub->shooting_frames[cub->shooting_active], 0, 0);
		i = 0;
	}
	cub->shooting_duration += 1;
}

void ft_star_shooting(t_cub *cub)
{
	cub->shooting_frames = ft_get_frames(cub, "../animation/shooting/", 7);
	if (cub->shooting_frames == NULL)
	{
		ft_printerror("shooting frames error\n");
		cub->shooting_active = 0;
	}
	cub->shooting_duration = 0;
	cub->shooting_active = 1;
}

void	ft_pov(void *arg)
{
	t_cub		*cub;

	cub = (t_cub *)arg;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE) && cub->shooting_active == 0)
    {
        mlx_delete_image(cub->mlx, cub->pov_normal);
		ft_star_shooting(cub);
    }
	ft_update_shooting(cub);
}
