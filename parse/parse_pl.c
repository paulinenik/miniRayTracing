/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:59:01 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 20:58:22 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_pl(char *line, t_scene *scene)
{
	t_plane *pl;
	t_list	*new;
	char	**arr;

	arr = ft_split(line, ' ');
	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl || !arr)
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "pl", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	pl->point = ato_xyz(arr[1], scene);
	pl->vector = ato_xyz(arr[2], scene);
	pl->color = atorgb(arr[3], scene);
	if (arr[4])
		ft_error_rt(MAP_INVALID, scene);
	new = ft_lstnew(pl);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_lstadd_back(&scene->pl, new);
	split_free(arr);
}
