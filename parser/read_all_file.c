/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:42:04 by moichou           #+#    #+#             */
/*   Updated: 2024/07/09 20:21:47 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*ft_read(int fd, char *result)
{
	char	*buffer;
	int		count;

	buffer = g_malloc(sizeof(char) * BUFFER_SIZE + 1, ALLOCATE);
	if (!buffer)
		return (result = NULL, NULL);
	count = 1;
	while (ft_strsearch(result, '\n') == 0 && result[0] != '\n')
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (free(buffer), NULL);
		if (count == 0)
			break ;
		buffer[count] = '\0';
		result = ft_strjoin(result, buffer);
		if (!result)
			break ;
	}
	return (free(buffer), result);
}

static char	*ft_extract_line(char *result)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (result[i] != '\n' && result[i])
		i++;
	if (result[i] == '\n')
		i++;
	str = g_malloc(sizeof(char) * i + 1, ALLOCATE);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = result[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	*ft_extract_rest(char *result)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (result[i] != '\n' && result[i])
		i++;
	if (result[i] == '\n')
		i++;
	str = g_malloc(sizeof(char) * ft_strlen(result + i) + 1, ALLOCATE);
	if (!str)
		return (result = NULL, NULL);
	j = 0;
	while (result[i] != '\0')
	{
		str[j] = result[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (result = NULL, str);
}

static char	*get_next_line(int fd)
{
	static char	*result;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (!result)
	{
		result = ft_strdup("");
		if (!result)
			return (NULL);
	}
	result = ft_read(fd, result);
	if (!result)
		return (NULL);
	if (result[0] == '\0')
		return (result = NULL, NULL);
	line = ft_extract_line(result);
	if (!line)
		return (result = NULL, NULL);
	result = ft_extract_rest(result);
	if (!result)
		return (free(line), result = NULL, NULL);
	return (line);
}

/*
	read all the file and returns a string.
	returns NULL if allocation fails or if file is empty.
*/
char	*read_all_file(int fd)
{
	char	*res;
	char	*line;

	line = get_next_line(fd);
	res = NULL;
	while (line)
	{
		if (line && line[0] != '\n')
			res = ft_strjoin(res, line);
		line = get_next_line(fd);
	}
	return (res);
}