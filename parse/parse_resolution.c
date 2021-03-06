/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:13:41 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:08:58 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char **arr;

	if (scene->r.height != -1)
		ft_error_rt(map_invalid, scene);
	arr = ft_split(line, ' ');
	if (arr[3])
		ft_error_rt(map_invalid, scene);
	if (!arr)
		ft_error_rt(malloc_err, scene);
	if (ft_strncmp(arr[0], "R", ft_strlen(arr[0])))
		ft_error_rt(map_invalid, scene);
	scene->r.width = rt_atoi(arr[1], scene);
	scene->r.height = rt_atoi(arr[2], scene);
	if (scene->r.width <= 0 || scene->r.height <= 0)
		ft_error_rt(map_r_err, scene);
	split_free(arr);
}
