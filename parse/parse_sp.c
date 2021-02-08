/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:12:36 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 16:58:50 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_sp(char *line, t_scene *scene)
{
	t_sphere *sp;
	t_list	*new;
	char	**arr;

	arr = ft_split(str, ' ');
	sp = (t_sphere *)malloc(sizeof (t_sphere));
	if (!sp || !arr)
	//malloc error
	if (ft_strncmp(arr[0], "sp", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	sp->center = ato_xyz(arr[1]);
	sp->diameter = ft_atof(arr[2]);
	sp->color = atorgb(arr[3]);
	// if (arr[4])
	// 	printf("map error extra chars\n");
	new = ft_lstnew(sp);
	if (!new)
	// malloc error
	ft_lstadd_back(&scene->sp, new);
	//free arr
}