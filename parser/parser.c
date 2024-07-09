/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:11:24 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 13:26:44 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	check_extension(char *ext, int i)
{
	i++;
	if (ext[i] == '\0' || ft_strcmp(&ext[i], "cub") != 0)
		return (ft_printerror(EXT_ERR), -1);
	return (0);
}

static int	check_filename(char *filename)
{
	int		i;
	bool	no_extension;

	i = 0;
	no_extension = true;
	while (filename[i])
	{
		if (filename[i] == '.')
		{
			if (check_extension(filename, i) == -1)
				return (-1);
			no_extension = false;
		}
		i++;
	}
	if (no_extension)
		return (ft_printerror(NO_EXT_ERR), -1);
	return (1);
}

// returns -1 when error and 1 in success
int	parser(int ac, char **filename)
{
	if (ac < 2 || ac > 2)
		return (ft_printerror("no valid arguments\n"), -1);
	if (check_filename(filename[1]) == -1)
		return (-1);
	if (map_vaidator(filename[1]))
		return (-1);
	return (1);
}
