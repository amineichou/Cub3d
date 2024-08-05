/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:28:26 by moichou           #+#    #+#             */
/*   Updated: 2024/08/02 17:27:17 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*get_row(char *map_str, int *i, int s_row)
{
	char	*row;
	int		j;

	j = 0;
	if (!map_str || !map_str[*i])
		return (NULL);
	row = g_malloc(sizeof(char) * s_row + 1, ALLOCATE);
	while (map_str[*i] && map_str[*i] != '\n')
	{
		row[j] = map_str[*i];
		j++;
		(*i)++;
	}
	while (j < s_row)
		row[j++] = ' ';
	row[j] = '\0';
	if (map_str[*i])
		(*i)++;
	return (row);
}

/*
    this function trun the string (map_str)
    to a 2D array (map)
*/
char	**make_map(char *map_str, int s_row, int s_clm)
{
	char	**map;
	char	*row;
	int		i;
	int		map_index;

	map = g_malloc(sizeof(char *) * (s_clm + 1), ALLOCATE);
	i = 0;
	row = get_row(map_str, &i, s_row);
	map_index = 0;
	while (row)
	{
		map[map_index] = row;
		row = get_row(map_str, &i, s_row);
		map_index++;
	}
	map[s_clm] = NULL;
	return (map);
}
