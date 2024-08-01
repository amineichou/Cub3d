/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:53:10 by moichou           #+#    #+#             */
/*   Updated: 2024/07/31 22:01:35 by skarim           ###   ########.fr       */
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

int main(void)
{
    t_cub   cub = {
        .mlx = NULL,
        .image = NULL,
        .player = {0},
        .map = {
            {'0','0','1','1','1','1','1','1','1','1','1','1','1'},
            {'0','1','0','0','0','0','0','0','0','0','0','0','1'},
            {'1','0','0','1','0','1','0','1','0','0','1','0','1'},
            {'1','0','0','0','0','0','0','0','0','0','0','0','1'},
            {'1','0','0','0','0','0','0','0','0','0','0','0','1'},
            {'1','0','0','0','0','0','0','0','0','1','0','0','1'},
            {'1','0','0','1','0','0','0','0','0','1','0','0','1'},
            {'1','0','0','0','1','0','0','0','0','0','1','0','1'},
            {'1','0','0','0','0','0','0','0','0','0','0','1','1'},
            {'1','1','1','1','1','1','1','1','1','1','1','1','1'},
        },
    };

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
    return (EXIT_SUCCESS);
}



// int	main(int ac, char **av)
// {
// 	t_config	*game_config;

// 	// atexit(leaks);
// 	game_config = parser(ac, av);
// 	if (game_config)
// 	{
// 		ft_start();
// 	}
// 	g_malloc(0, FREE);
// 	return (0);
// }