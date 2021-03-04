/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:12:36 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/04 22:06:07 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sp(char *line, t_scene *scene)
{
	t_sphere	*sp;
	t_list		*new;
	char		**arr;

	arr = ft_split(line, ' ');
	if (arr[4])
		ft_error_rt(MAP_INVALID, scene);
	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp || !arr)
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "sp", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	sp->center = ato_xyz(arr[1], scene);
	sp->diameter = ft_atof(arr[2], scene);
	sp->color = atorgb(arr[3], scene);
	sp->r = 0;
	new = ft_lstnew(sp);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_lstadd_back(&scene->sp, new);
	split_free(arr);
}
