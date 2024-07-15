/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:11:24 by moichou           #+#    #+#             */
/*   Updated: 2024/07/15 16:44:53 by moichou          ###   ########.fr       */
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
	in success returns config struct that has args
	(including the map in a 2d array),
	when error and -1.
*/
t_config	*parser(int ac, char **av)
{
	t_config	*game_config;

	if (ac < 2 || ac > 2)
		return (ft_printerror(PARSE_ERR), NULL);
	if (check_valid_filename(av[1]) == -1)
		return (NULL);
	game_config = make_config(av[1]);
	if (!game_config)
		return (NULL);
	return (game_config);
}
