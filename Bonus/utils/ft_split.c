/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:54:37 by moichou           #+#    #+#             */
/*   Updated: 2024/07/11 13:55:51 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static size_t	ft_count_delimiters(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**fill_the_splited(char **splited, const char *str, char c)
{
	int	splited_i;
	int	index;
	int	str_len;

	splited_i = 0;
	index = 0;
	while (str[index])
	{
		str_len = 0;
		while (str[index] == c)
			index++;
		while (str[index] != c && str[index])
		{
			str_len++;
			index++;
		}
		if (str_len == 0)
			break ;
		splited[splited_i] = g_malloc(sizeof(char) * (str_len + 1), ALLOCATE);
		if (!splited[splited_i])
			return (NULL);
		ft_strlcpy(splited[splited_i], &str[index] - str_len, str_len + 1);
		splited_i += 1;
	}
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		count_del;

	if (!s)
		return (0);
	count_del = ft_count_delimiters(s, c);
	splited = g_malloc(sizeof(char *) * (count_del + 1), ALLOCATE);
	if (!splited)
		return (NULL);
	if (!fill_the_splited(splited, s, c))
		return (NULL);
	splited[count_del] = 0;
	return (splited);
}
