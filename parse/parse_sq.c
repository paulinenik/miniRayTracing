/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:02:50 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 17:07:41 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_sq(char *line, t_scene *scene)
{
	t_square *sq;
	t_list	*new;
	char	**arr;

	arr = ft_split(line, ' ');
	sq = (t_square *)malloc(sizeof (t_square));
	if (!sq || !arr)
	//malloc error
	if (ft_strncmp(arr[0], "sq", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	sq->center = ato_xyz(arr[1]);
	sq->vector = ato_xyz(arr[2]);
	sq->sidesize = ft_atof(arr[3])
	sq->color = atorgb(arr[4]);
	// if (arr[5])
	// 	printf("map error extra chars\n");
	new = ft_lstnew(sq);
	if (!new)
	// malloc error
	ft_lstadd_back(&scene->sq, new);
	//free arr
}