/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:02:55 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 17:00:53 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	map_vaidator(char *filename)
{
	char	*file;
	// char	**map;
	int		fd;

	fd = open(filename, O_RDONLY, 777);
	if (fd == -1)
		return (ft_printerror(OPEN_ERR), -1);
	file = read_all_file(fd);
	if (!file)
		return (ft_printerror("emty file\n"), -1);
	return (1);
}
