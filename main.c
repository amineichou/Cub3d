/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:53:10 by moichou           #+#    #+#             */
/*   Updated: 2024/07/13 17:43:06 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	leaks(void)
// {
// 	system("leaks cub3d");
// }

int	main(int ac, char **av)
{
	// atexit(leaks);
	if (parser(ac, av))
	{
		// code here
	}
	g_malloc(0, FREE);
	return (0);
}