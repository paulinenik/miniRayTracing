/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:10:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 17:12:25 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_tr(char *line, t_scene *scene)
{
	t_triangle *tr;
	t_list	*new;
	char	**arr;

	arr = ft_split(line, ' ');
	tr = (t_triangle *)malloc(sizeof (t_triangle));
	if (!tr || !arr)
	//malloc error
	if (ft_strncmp(arr[0], "tr", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	tr->p1 = ato_xyz(arr[1]);
	tr->p2 = ato_xyz(arr[2]);
	tr->p3 = ato_xyz(arr[3]);
	tr->color = atorgb(arr[4]);
	// if (arr[5])
	// 	printf("map error extra chars\n");
	new = ft_lstnew(tr);
	if (!new)
	// malloc error
	ft_lstadd_back(&scene->tr, new);
	//free arr
}