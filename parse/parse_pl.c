/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:59:01 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 17:07:33 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_pl(char *line, t_scene *scene)
{
	t_plane *pl;
	t_list	*new;
	char	**arr;

	arr = ft_split(str, ' ');
	pl = (t_plane *)malloc(sizeof (t_plane));
	if (!pl || !arr)
	//malloc error
	if (ft_strncmp(arr[0], "pl", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	pl->point = ato_xyz(arr[1]);
	pl->vector = ato_xyz(arr[2]);
	pl->color = atorgb(arr[3]);
	// if (arr[4])
	// 	printf("map error extra chars\n");
	new = ft_lstnew(pl);
	if (!new)
	// malloc error
	ft_lstadd_back(&scene->pl, new);
	//free arr
}