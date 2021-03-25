/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:17:20 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:06:58 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	parse_ambient(char *line, t_scene *scene)
{
	char **arr;

	if (scene->a.bright != -1)
		ft_error_rt(map_invalid, scene);
	arr = ft_split(line, ' ');
	if (arr[3])
		ft_error_rt(map_invalid, scene);
	if (!arr)
		ft_error_rt(malloc_err, scene);
	if (ft_strncmp(arr[0], "A", ft_strlen(arr[0])))
		ft_error_rt(map_invalid, scene);
	scene->a.bright = ft_atof(arr[1], scene);
	if (scene->a.bright < 0 || scene->a.bright > 1)
		ft_error_rt(map_bright_err, scene);
	scene->a.color = atorgb(arr[2], scene);
	split_free(arr);
}
