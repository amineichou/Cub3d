/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:11:24 by moichou           #+#    #+#             */
/*   Updated: 2024/07/11 15:35:16 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	check_valid_filename(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension)
		return (ft_printerror(EXT_ERR), -1);
	if (ft_strcmp(extension, ".cub") != 0)
		return (ft_printerror(EXT_ERR), -1);
	return (1);
}

/*
	checks the map file name, existence and format.
	also checks the configuration (valid args and map).
	returns -1 when error and 1 in success.
*/
int	parser(int ac, char **av)
{
	t_config	*game_config;

	if (ac < 2 || ac > 2)
		return (ft_printerror("no valid arguments\n"), -1);
	if (check_valid_filename(av[1]) == -1)
		return (-1);
	game_config = make_config(av[1]);
	if (!game_config)
		return (-1);
	return (1);
}
