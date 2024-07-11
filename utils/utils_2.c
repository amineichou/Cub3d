/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:44:12 by moichou           #+#    #+#             */
/*   Updated: 2024/07/10 21:23:05 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_strjoin(char *first, char *second)
{
	char	*res;
	int		i;
	int		j;

	if (!first)
		return (ft_strdup(second));
	else if (!second)
		return (ft_strdup(first));
	res = g_malloc(sizeof(char) * (ft_strlen(first) + ft_strlen(second) + 1), ALLOCATE);
	if (!res)
		return (first = NULL, NULL);
	i = 0;
	j = 0;
	while (first[j])
		res[i++] = first[j++];
	j = 0;
	while (second[j])
		res[i++] = second[j++];
	res[i] = '\0';
	return (res);
}

int	ft_strsearch(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strldup(char *s1, int lenght)
{
	int		i;
	char	*s2;

	i = 0;
	if (ft_strlen(s1) < lenght)
		return (NULL);
	s2 = g_malloc(sizeof(char) * (lenght + 1), ALLOCATE);
	if (!s2)
		return (NULL);
	while (i < lenght)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[lenght] = '\0';
	return (s2);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

/*
	this function checks if the the string is empty
	and returns 1, else if not returns 0
*/
int	ft_isemptystr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
