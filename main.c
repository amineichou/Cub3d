/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:53:10 by moichou           #+#    #+#             */
/*   Updated: 2024/07/15 16:30:37 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	leaks(void)
// {
// 	system("leaks cub3d");
// }

int	main(int ac, char **av)
{
	t_config	*game_config;

	// atexit(leaks);
	game_config = parser(ac, av);
	if (game_config)
	{
		// code here
	}
	g_malloc(0, FREE);
	return (0);
}