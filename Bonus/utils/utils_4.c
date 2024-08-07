/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:53:09 by moichou           #+#    #+#             */
/*   Updated: 2024/08/07 11:46:57 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
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

bool	is_door(char c)
{
	if (c == 'D')
		return (true);
	return (false);
}