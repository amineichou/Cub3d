/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:40:56 by moichou           #+#    #+#             */
/*   Updated: 2024/09/05 15:29:00 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

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
	atoi but returns color values only
*/
int	ft_atoi_color(const char *str)
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
		if (res > 255 || sign == -1)
			return (ft_printerror("invalid color value\n"),
				g_malloc(0, FREE), exit(1), -1);
		i++;
	}
	return (res * sign);
}

/*
	** get the player position in the map
	** and set the player angle according to the player's Charachter
	** return 1 if the player is found
	** return 0 if the player is not found
*/
int	ft_get_player_postion(t_player *player, char **map, int x, int y)
{
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				player->xposition = x;
				player->yposition = y;
				if (map[y][x] == 'S')
					player->angle = 3 * M_PI / 2;
				else if (map[y][x] == 'N')
					player->angle = M_PI / 2;
				else if (map[y][x] == 'W')
					player->angle = M_PI;
				else if (map[y][x] == 'E')
					player->angle = 0;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (ft_printerror("There's no player in the map!\n"), 0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
