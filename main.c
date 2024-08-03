/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:53:10 by moichou           #+#    #+#             */
/*   Updated: 2024/08/03 13:34:53 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	leaks(void)
// {
// 	system("leaks cub3d");
// }


void    ft_hook(void* param)
{
    t_cub*  cub;
    
    cub = param;
    if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cub->mlx);
    update_player_position(cub);
    clear_image(cub->image);
	cast_rays(cub);
    draw_3d(cub);
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

int main(int ac, char **av)
{
    t_config	*game_config;
    game_config = parser(ac, av);
    if (!game_config)
        return (EXIT_FAILURE);

    // int x;
    // int y;
    // y = 0;
    // while (game_config->map[y])
    // {
    //     x = 0;
    //     while (game_config->map[y][x])
    //     {
    //       printf("%c", game_config->map[y][x]);
    //     x++;
    //     }
    //     printf("\n");
    //     y++;
    // }
    
    t_cub   cub = {
        .mlx = NULL,
        .image = NULL,
        .player = {0},
        .map = game_config->map,
    };
    if (!ft_get_player_postion(&cub.player, cub.map))
        return (EXIT_FAILURE);
    if (!(cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
    {
        perror(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (!(cub.image = mlx_new_image(cub.mlx, WIDTH, HEIGHT)))
    {
        mlx_close_window(cub.mlx);
        perror(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    printf("[%f , %f]\n", cub.player.xposition, cub.player.yposition);
    ft_init_player(&cub.player);
    if (mlx_image_to_window(cub.mlx, cub.image, 0, 0) == -1)
    {
        mlx_close_window(cub.mlx);
        perror(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    mlx_image_to_window(cub.mlx, cub.image, 0, 0);
    mlx_loop_hook(cub.mlx, ft_hook, &cub);
    mlx_loop(cub.mlx);
    mlx_terminate(cub.mlx);
    g_malloc(0, FREE);
    return (EXIT_SUCCESS);
}