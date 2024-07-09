/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:32:15 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 21:40:05 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
	checks file args and return a struct
	if a problem acurred it returns NULL
*/
t_config	*check_file_content(char *filename)
{
	t_config	*config;
	char		*file_content;
	int			fd;

	fd = open(filename, O_RDONLY, 777);
	if (fd == -1)
		return (ft_printerror(OPEN_ERR), NULL);
	file_content = read_all_file(fd);
	if (!file_content)
		return (ft_printerror("emty file\n"), NULL);
	config = g_malloc(sizeof(t_config), ALLOCATE);
	if (!config)
		return (NULL);
	printf("%s\n", file_content);
	return (NULL);
}

