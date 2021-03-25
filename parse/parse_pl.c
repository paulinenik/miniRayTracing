/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:59:01 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:08:37 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

void	parse_pl(char *line, t_scene *scene)
{
	t_plane *pl;
	t_list	*new;
	char	**arr;

	arr = ft_split(line, ' ');
	if (arr[4])
		ft_error_rt(map_invalid, scene);
	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl || !arr)
		ft_error_rt(malloc_err, scene);
	if (ft_strncmp(arr[0], "pl", ft_strlen(arr[0])))
		ft_error_rt(map_invalid, scene);
	pl->point = ato_xyz(arr[1], scene);
	pl->vector = ato_xyz(arr[2], scene);
	pl->color = atorgb(arr[3], scene);
	new = ft_lstnew(pl);
	if (!new)
		ft_error_rt(malloc_err, scene);
	ft_lstadd_back(&scene->pl, new);
	split_free(arr);
}
