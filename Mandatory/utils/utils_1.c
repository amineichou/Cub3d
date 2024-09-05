/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:00:33 by moichou           #+#    #+#             */
/*   Updated: 2024/09/05 11:24:10 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_printerror(char *msg)
{
	int	i;

	i = 0;
	write (2, "Error\n", 7);
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

/*
	locates the last occurrence of c in s
	returns NULL if there's no c in s
*/
char	*ft_strrchr(char *s, int c)
{
	int		i;
	int		slen;
	char	*last;
	char	*source;

	i = 0;
	source = (char *)s;
	last = NULL;
	slen = ft_strlen(s);
	while (i <= slen)
	{
		if (source[i] == (char)c)
			last = &source[i];
		i++;
	}
	return (last);
}

char	*ft_strdup(char *s1)
{
	int		str_length;
	int		i;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	str_length = ft_strlen(s1) + 1;
	s2 = g_malloc(sizeof(char) * str_length, ALLOCATE);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
