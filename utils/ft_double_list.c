/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:28:40 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:18:29 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

t_dlist	*ft_dlstnew(void *data)
{
	t_dlist *new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_dlstadd(t_dlist **lst, t_dlist *new)
{
	if (*lst && (*lst)->next)
	{
		new->next = (*lst)->next;
		(*lst)->next = new;
		(*lst) = new->next;
		new->prev = (*lst)->prev;
		(*lst)->prev = new;
	}
	else if (*lst && !(*lst)->next)
	{
		(*lst)->next = new;
		(*lst)->prev = new;
		new->next = *lst;
		new->prev = *lst;
	}
	else
		*lst = new;
}

void	ft_dlist_clear(t_dlist **lst)
{
	t_dlist	*temp;

	if ((*lst)->prev != NULL)
		(*lst)->prev->next = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = temp;
	}
}
