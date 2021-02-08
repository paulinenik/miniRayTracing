/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:33:54 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 16:48:21 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_light(char *str, t_scene *scene)
{
	t_light *l;
	t_list	*new;
	char	**arr;

	arr = ft_split(str, ' ');
	l = (t_light *)malloc(sizeof (t_light));
	if (!l || !arr)
	//malloc error
	if (ft_strncmp(arr[0], "l", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	l->point = ato_xyz(arr[1]);
	l->bright = ft_atof(arr[2]);
	l->color = atorgb(arr[3]);
	// if (arr[4])
	// 	printf("map error extra chars\n");
	new = ft_lstnew(l);
	if (!new)
	// malloc error
	ft_lstadd_back(&scene->light, new);
	//free arr
}



	