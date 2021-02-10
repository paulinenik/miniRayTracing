/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:06:17 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 20:01:16 by rgordon          ###   ########.fr       */
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
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "cy", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	cy->point = ato_xyz(arr[1], scene);
	cy->vector = ato_xyz(arr[2], scene);
	cy->diameter = ft_atof(arr[3], scene);
	cy->height = ft_atof(arr[4], scene);
	cy->color = atorgb(arr[5], scene);
	if (arr[6])
	 	ft_error_rt(MAP_INVALID, scene);
	new = ft_lstnew(cy);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_lstadd_back(&scene->cy, new);
	split_free(arr);
}