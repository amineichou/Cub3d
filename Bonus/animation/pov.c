/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:38:38 by moichou           #+#    #+#             */
/*   Updated: 2024/08/12 21:31:40 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

#define SHOOTING_ANIMATION_FRAMES 11
#define FRAME_DURATION 100000000

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
    // Ensure that shooting is active and frames are valid
    if (!cub->shooting_active || cub->shooting_frames == NULL)
        return;

    // Update frames based on the elapsed time
    while (mlx_get_time() - cub->last_frame_time > FRAME_DURATION)
    {
        // Check if current_frame is within bounds
        if (cub->current_frame < SHOOTING_ANIMATION_FRAMES)
        {
            // Display the current frame
			if (!mlx_resize_image(cub->shooting_frames[cub->current_frame], WIDTH, HEIGHT))
            mlx_image_to_window(cub->mlx, cub->shooting_frames[cub->current_frame], 0, 0);

            // Delete the previous frame (if applicable)
            if (cub->current_frame > 0)
                mlx_delete_image(cub->mlx, cub->shooting_frames[cub->current_frame - 1]);

            // Increment frame index
            cub->current_frame++;
        }

        // Check if the animation has reached the last frame
        if (cub->current_frame >= SHOOTING_ANIMATION_FRAMES)
        {
            cub->shooting_active = 0; // Deactivate shooting
            cub->current_frame = 0;   // Reset the frame index
            break;                    // Exit the loop
        }

        // Move to the next frame time
        cub->last_frame_time += FRAME_DURATION;
    }

    // Update the time for the next frame
    cub->last_frame_time = mlx_get_time();
}

void ft_star_shooting(t_cub *cub)
{
    cub->shooting_active = 1;
    cub->current_frame = 0;
    cub->last_frame_time = mlx_get_time();

    // Ensure that shooting frames are properly allocated
    cub->shooting_frames = ft_get_frames(cub, "../animation/shooting/", SHOOTING_ANIMATION_FRAMES);
    if (cub->shooting_frames == NULL)
    {
        // Handle the error (e.g., log it, deactivate shooting, etc.)
        cub->shooting_active = 0;
    }
}

void	ft_pov(void *arg)
{
	t_cub		*cub;

	cub = (t_cub *)arg;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_SPACE))
		ft_star_shooting(cub);
	ft_update_shooting(cub);
}
