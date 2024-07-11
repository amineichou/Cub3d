/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:37:05 by moichou           #+#    #+#             */
/*   Updated: 2024/07/11 17:05:19 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	**ft_divide_str(char *str)
{
	char	**res;
	int		i;

	i = 0;
	res = g_malloc(sizeof(char *) * (2 + 1), ALLOCATE);
	while (str[i] && !ft_isspace(str[i]))
		i++;
	res[0] = ft_strldup(str, i);
	res[1] = ft_strdup(&str[i]);
	res[2] = NULL;
	return (res);
}

/*
    remove the spaces and tabs from the start
    and the end of a string
*/
char	*ft_trim_spaces(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	j = ft_strlen(str) - 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (ft_isspace(str[j]))
		j--;
	j = ft_strlen(str) - j - 1;
	res = ft_strldup(str + i, (ft_strlen(str) - i - j));
	if (!res)
		return (ft_printerror(MALLOC_ERR), NULL);
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
