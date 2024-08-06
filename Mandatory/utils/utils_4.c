/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:40:56 by moichou           #+#    #+#             */
/*   Updated: 2024/08/05 22:47:49 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int ft_atoi(const char *str)
{
    int sign = 1;
    int result = 0;
    int i = 0;

    // Skip whitespace characters
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
    {
        i++;
    }

    // Check for optional sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            sign = -1;
        }
        i++;
    }

    // Convert digits to integer
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

mlx_image_t	*ft_get_image(t_cub *cub, char *pathname)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	pathname++;
	texture = mlx_load_png(pathname);
	printf("%s\n", pathname);
	if (!texture)
	{
		ft_printerror("texture file error to open\n");
		exit(1);
	}
	image = mlx_texture_to_image(cub->mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}