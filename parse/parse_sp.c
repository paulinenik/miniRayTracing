/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:12:36 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/26 21:33:47 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

void	parse_sp(char *line, t_scene *scene)
{
	t_sphere	*sp;
	t_list		*new;
	char		**arr;

	arr = ft_split(line, ' ');
	if (arr[4])
		ft_error_rt(map_invalid, scene);
	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp || !arr)
		ft_error_rt(malloc_err, scene);
	if (ft_strncmp(arr[0], "sp", ft_strlen(arr[0])))
		ft_error_rt(map_invalid, scene);
	sp->center = ato_xyz(arr[1], scene);
	sp->color = atorgb(arr[3], scene);
	sp->r = ft_atof(arr[2], scene) / 2;
	if (sp->r <= 0)
		ft_error_rt(map_invalid, scene);
	new = ft_lstnew(sp);
	if (!new)
		ft_error_rt(malloc_err, scene);
	ft_lstadd_back(&scene->sp, new);
	split_free(arr);
}
