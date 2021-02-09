/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:10:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/09 23:41:02 by rgordon          ###   ########.fr       */
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
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "tr", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	tr->p1 = ato_xyz(arr[1], scene);
	tr->p2 = ato_xyz(arr[2], scene);
	tr->p3 = ato_xyz(arr[3], scene);
	tr->color = atorgb(arr[4], scene);
	if (arr[5])
		ft_error_rt(MAP_INVALID, scene);
	new = ft_lstnew(tr);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_lstadd_back(&scene->tr, new);
	//free arr
}