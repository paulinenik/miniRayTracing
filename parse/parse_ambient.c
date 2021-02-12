/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:17:20 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 20:58:22 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char *line, t_scene *scene)
{
	char **arr;

	if (scene->a.bright != -1)
		ft_error_rt(MAP_INVALID, scene);
	arr = ft_split(line, ' ');
	if (!arr)
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "A", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	scene->a.bright = ft_atof(arr[1], scene);
	if (scene->a.bright < 0 || scene->a.bright > 1)
		ft_error_rt(MAP_BRIGHT_ERR, scene);
	scene->a.color = atorgb(arr[2], scene);
	if (arr[3])
		ft_error_rt(MAP_INVALID, scene);
	split_free(arr);
}
