/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:02:50 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/04 22:06:28 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sq(char *line, t_scene *scene)
{
	t_square	*sq;
	t_list		*new;
	char		**arr;

	arr = ft_split(line, ' ');
	if (arr[5])
		ft_error_rt(MAP_INVALID, scene);
	sq = (t_square *)malloc(sizeof(t_square));
	if (!sq || !arr)
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "sq", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	sq->center = ato_xyz(arr[1], scene);
	sq->vector = ato_xyz(arr[2], scene);
	sq->sidesize = ft_atof(arr[3], scene);
	sq->color = atorgb(arr[4], scene);
	new = ft_lstnew(sq);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_lstadd_back(&scene->sq, new);
	split_free(arr);
}
