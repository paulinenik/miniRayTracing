/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:33:54 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 02:17:20 by rgordon          ###   ########.fr       */
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
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "l", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	l->point = ato_xyz(arr[1], scene);
	l->bright = ft_atof(&arr[2], scene);
	if (l->bright < 0 || l->bright > 1)
		ft_error_rt(MAP_BRIGHT_ERR, scene);
	l->color = atorgb(arr[3], scene);
	if (arr[4])
		ft_error_rt(MAP_INVALID, scene);
	new = ft_lstnew(l);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_lstadd_back(&scene->light, new);
	//free arr
}



	