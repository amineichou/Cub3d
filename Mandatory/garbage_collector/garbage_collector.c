/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moichou <moichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:08:43 by moichou           #+#    #+#             */
/*   Updated: 2024/09/05 21:43:56 by moichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub.h"

static void	g_free(t_garbage *lst)
{
	t_garbage	*tofree;

	while (lst)
	{
		tofree = lst;
		lst = lst->next;
		free(tofree->allocated);
		tofree->allocated = NULL;
		tofree = NULL;
	}
	lst = NULL;
}

static void	appand_to_lst(t_garbage **lst, t_garbage *node)
{
	t_garbage	*tmp;

	if ((*lst) == NULL)
	{
		(*lst) = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/*
	take two modes ALLOCATE/FREE, returns a pointer to the mallocated 
	region in ALLOCATE mode if alloaction fails it returns NULL,
	returns NULL in FREE mode
*/
void	*g_malloc(size_t size, t_g_malloc mode)
{
	static t_garbage	*lst;
	t_garbage			*node;

	if (mode == ALLOCATE)
	{
		node = malloc(sizeof(t_garbage));
		if (!node)
		{
			ft_printerror(MALLOC_ERR);
			g_free(lst);
			exit(1);
		}
		node->next = NULL;
		appand_to_lst(&lst, node);
		node->allocated = malloc(size);
		if (node->allocated)
			return (node->allocated);
		ft_printerror(MALLOC_ERR);
		g_free(lst);
		exit(1);
	}
	else if (mode == FREE)
		g_free(lst);
	return (NULL);
}
