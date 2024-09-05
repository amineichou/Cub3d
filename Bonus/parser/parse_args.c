/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:23:10 by moichou           #+#    #+#             */
/*   Updated: 2024/09/05 17:59:30 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

int	parse_args_f(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->f[i])
	{
		j = 0;
		config->f[i] = ft_trim_spaces(config->f[i]);
		if (!config->f[i])
			return (ft_printerror(PARSE_ERR), -1);
		while (config->f[i][j])
		{
			if (!ft_isdigit(config->f[i][j]))
				return (ft_printerror(PARSE_ERR), -1);
			j++;
		}
		if (i >= 4)
			return (ft_printerror(PARSE_ERR), -1);
		i++;
	}
	if (i < 3)
		return (ft_printerror(PARSE_ERR), -1);
	return (1);
}

int	parse_args_c(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->c[i])
	{
		j = 0;
		config->c[i] = ft_trim_spaces(config->c[i]);
		if (!config->c[i])
			return (ft_printerror(PARSE_ERR), -1);
		while (config->c[i][j])
		{
			if (!ft_isdigit(config->c[i][j]))
				return (ft_printerror(PARSE_ERR), -1);
			j++;
		}
		if (i >= 4)
			return (ft_printerror(PARSE_ERR), -1);
		i++;
	}
	if (i < 3)
		return (ft_printerror(PARSE_ERR), -1);
	return (1);
}
