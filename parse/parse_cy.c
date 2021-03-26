/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:06:17 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/26 21:36:18 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

void	parse_cy(char *line, t_scene *scene)
{
	t_cylinder	*cy;
	t_list		*new;
	char		**arr;

	arr = ft_split(line, ' ');
	if (arr[6])
		ft_error_rt(map_invalid, scene);
	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy || !arr)
		ft_error_rt(malloc_err, scene);
	if (ft_strncmp(arr[0], "cy", ft_strlen(arr[0])))
		ft_error_rt(map_invalid, scene);
	cy->point = ato_xyz(arr[1], scene);
	cy->vector = normalize(ato_xyz(arr[2], scene));
	cy->r = ft_atof(arr[3], scene) / 2;
	cy->height = ft_atof(arr[4], scene);
	cy->color = atorgb(arr[5], scene);
	if (cy->r <= 0 || cy->height <= 0)
		ft_error_rt(map_invalid, scene);
	new = ft_lstnew(cy);
	if (!new)
		ft_error_rt(malloc_err, scene);
	ft_lstadd_back(&scene->cy, new);
	split_free(arr);
}
