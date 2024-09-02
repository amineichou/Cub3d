/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:53:10 by moichou           #+#    #+#             */
/*   Updated: 2024/09/02 20:49:40 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	update_player_position(cub);
	cast_rays(cub);
	draw_3d(cub);
	ft_minimap(cub);
}

/*
	Move left (decrease x), if xpos indicates leftward movement
	Move right (increase x), if xpos indicates rightward movement
*/
void	ft_mouse_move(double xpos, double ypos, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (xpos > cub->player.xpixel)
	{
		cub->player.angle = ft_periodic(cub->player.angle
				- cub->player.turn_speed);
	}
	else if (xpos < cub->player.xpixel)
	{
		cub->player.angle = ft_periodic(cub->player.angle
				+ cub->player.turn_speed);
	}
}

void	ft_load_images(t_cub *cub, t_config *game_config)
{
	cub->no = ft_get_image(cub, game_config->no);
	cub->so = ft_get_image(cub, game_config->so);
	cub->we = ft_get_image(cub, game_config->we);
	cub->ea = ft_get_image(cub, game_config->ea);
	cub->door = ft_get_image(cub, "./textures/door.png");
	cub->pov_normal = ft_get_image(cub, "./textures/normal.png");
	if (!mlx_resize_image(cub->pov_normal, WIDTH, HEIGHT))
	{
		ft_printerror("resize error\n");
		exit(1);
	}
}

void	init_floor_ceil_color(t_cub *cub, t_config *game_config)
{
	cub->f[0] = ft_atoi_color(game_config->f[0]);
	cub->f[1] = ft_atoi_color(game_config->f[1]);
	cub->f[2] = ft_atoi_color(game_config->f[2]);
	if (game_config->f[3] == NULL)
		cub->f[3] = 255;
	else
		cub->f[3] = ft_atoi_color(game_config->f[3]);
	cub->c[0] = ft_atoi_color(game_config->c[0]);
	cub->c[1] = ft_atoi_color(game_config->c[1]);
	cub->c[2] = ft_atoi_color(game_config->c[2]);
	if (game_config->c[3] == NULL)
		cub->c[3] = 255;
	else
		cub->c[3] = ft_atoi_color(game_config->c[3]);
}

void	ft_init_cub(t_cub *cub, t_config *game_config)
{
	if (!(cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
	{
		perror(mlx_strerror(mlx_errno));
		return ;
	}
	cub->map = game_config->map;
	init_floor_ceil_color(cub, game_config);
	cub->mapx = game_config->mapx;
	cub->mapy = game_config->mapy;
	if (!ft_get_player_postion(&cub->player, cub->map, 0, 0))
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
	t_cub		cub;

	game_config = parser(ac, av);
	if (!game_config)
	    return (EXIT_FAILURE);
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
