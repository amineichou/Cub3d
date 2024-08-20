/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:53:10 by moichou           #+#    #+#             */
/*   Updated: 2024/08/19 21:43:58 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	leaks(void)
// {
// 	system("leaks cub3d");
// }


void    ft_hook(void *param)
{
    t_cub*  cub;
    
    cub = (t_cub*)param;
    if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cub->mlx);
    update_player_position(cub);
    clear_image(cub->image);
	cast_rays(cub);
    draw_3d(cub);
    ft_minimap(cub);
    // drawMinimap(cub);
}

#include <math.h>

void	ft_mouse_move(double xpos, double ypos, void *param)
{
	t_cub	*cub;
	cub = (t_cub *)param;
	// Move right (increase x), if xpos indicates rightward movement
	if (xpos > cub->player.xpixel)
	{
		cub->player.angle = ft_periodic(cub->player.angle
				- cub->player.turn_speed);
	}
	// Move left (decrease x), if xpos indicates leftward movement
	else if (xpos < cub->player.xpixel)
	{
		cub->player.angle = ft_periodic(cub->player.angle
				+ cub->player.turn_speed);
	}
}


int ft_get_player_postion(t_player *player, char **map)
{
	int	x;
	int	y;

	x = 0;
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
    ft_printerror("There's no player in the map!\n");
    return (0);
}

void	ft_load_images(t_cub *cub, t_config *game_config)
{
	cub->no = ft_get_image(cub, game_config->no);
	cub->so = ft_get_image(cub, game_config->so);
	cub->we = ft_get_image(cub, game_config->we);
	cub->ea = ft_get_image(cub, game_config->ea);
	    // load door and pov_normal images
    cub->door = ft_get_image(cub, "../textures/door.png");
    cub->pov_normal = ft_get_image(cub, "../textures/normal.png");
    if (!mlx_resize_image(cub->pov_normal, WIDTH, HEIGHT))
    {
        ft_printerror("resize error\n");
        exit(1);
    }
}

void	ft_init_cub(t_cub *cub, t_config *game_config)
{
	if (!(cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
    {
        perror(mlx_strerror(mlx_errno));
        return ;
    }
	cub->map = game_config->map;
	cub->f[3] = 255;
	cub->c[3] = 255;
    if (!ft_get_player_postion(&cub->player, cub->map))
        return ;
	ft_load_images(cub, game_config);
	ft_init_player(&(cub->player));
	if (!(cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT)))
    {
        mlx_close_window(cub->mlx);
        perror(mlx_strerror(mlx_errno));
        return ;
    }
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1)
    {
        mlx_close_window(cub->mlx);
        perror(mlx_strerror(mlx_errno));
        return ;
    }
    cub->shooting_active = 0;
}

int main(int ac, char **av)
{
    t_config	*game_config;
    game_config = parser(ac, av);
    if (!game_config)
        return (EXIT_FAILURE);
    t_cub   cub;
    ft_init_cub(&cub, game_config);
	mlx_image_to_window(cub.mlx, cub.image, 0, 0);
    mlx_image_to_window(cub.mlx, cub.pov_normal, 0, 0);
    mlx_loop_hook(cub.mlx, ft_hook, &cub);
    mlx_loop_hook(cub.mlx, ft_pov, &cub);
    mlx_cursor_hook(cub.mlx, ft_mouse_move, &cub);
    mlx_loop(cub.mlx);
    mlx_terminate(cub.mlx);
    g_malloc(0, FREE);
    return (EXIT_SUCCESS);
}
