/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:06:17 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 17:10:29 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cy(char *line, t_scene *scene)
{
	t_cylinder *cy;
	t_list	*new;
	char	**arr;

	arr = ft_split(line, ' ');
	cy = (t_cylinder *)malloc(sizeof (t_cylinder));
	if (!cy || !arr)
	//malloc error
	if (ft_strncmp(arr[0], "cy", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	cy->point = ato_xyz(arr[1]);
	cy->vector = ato_xyz(arr[2]);
	cy->diameter = ft_atof(arr[3]);
	cy->height = ft_atof(arr[4]);
	cy->color = atorgb(arr[5]);
	// if (arr[6])
	// 	printf("map error extra chars\n");
	new = ft_lstnew(cy);
	if (!new)
	// malloc error
	ft_lstadd_back(&scene->cy, new);
	//free arr
}