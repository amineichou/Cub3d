/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:38:38 by moichou           #+#    #+#             */
/*   Updated: 2024/08/21 18:34:42 by moichou          ###   ########.fr       */
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
			return (ft_printerror("get image error\n"), exit(1), NULL);
		if (!mlx_resize_image(image, WIDTH, HEIGHT))
			return (ft_printerror("resize image error\n"), exit(1), NULL);
		images[i] = image;
		i++;
	}
	images[i] = NULL;
	return (images);
}

void ft_end_shooting(t_cub *cub)
{
	cub->shooting_active = false;
	cub->shooting_frames_count = 0;
	cub->pov_normal = ft_get_image(cub, "../textures/normal.png");
	if (!mlx_resize_image(cub->pov_normal, WIDTH, HEIGHT))
	{
		ft_printerror("resize error\n");
		exit(1);
	}
	mlx_image_to_window(cub->mlx, cub->pov_normal, 0, 0);
}

void ft_update_shooting(t_cub *cub)
{
	static int	first;

	if (!cub->shooting_active)
		return;
	if (first == 0)
	{
		mlx_image_to_window(cub->mlx, cub->shooting_frames[cub->shooting_frames_count], 0, 0);
		first = 1;
	}
	if (cub->shooting_duration >= 5)
	{
		mlx_delete_image(cub->mlx, cub->shooting_frames[cub->shooting_frames_count]);
		cub->shooting_frames_count++;
		if (cub->shooting_frames[cub->shooting_frames_count] == NULL)
		{
			first = 0;
			ft_end_shooting(cub);
			return ;
		}
		mlx_image_to_window(cub->mlx, cub->shooting_frames[cub->shooting_frames_count], 0, 0);
		cub->shooting_duration = 0;
	}
	else
		cub->shooting_duration++;
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
	cub->shooting_active = true;
	cub->shooting_frames_count = 0;
}

void	ft_pov(void *arg)
{
	t_cub		*cub;

	cub = (t_cub *)arg;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE) && !cub->shooting_active)
	{
		if (fork() == 0)
		{
			system("afplay ./animation/gun-shot.wav");
			exit(0);
		}
		else {
	        mlx_delete_image(cub->mlx, cub->pov_normal);
			ft_star_shooting(cub);
		}
	}
	ft_update_shooting(cub);
}
