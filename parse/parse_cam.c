/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:24:46 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/26 21:37:54 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

void	parse_cam(char *line, t_scene *scene)
{
	t_camera	*cam;
	t_dlist		*new;
	char		**arr;

	arr = ft_split(line, ' ');
	if (arr[4])
		ft_error_rt(map_invalid, scene);
	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam || !arr)
		ft_error_rt(malloc_err, scene);
	if (ft_strncmp(arr[0], "c", ft_strlen(arr[0])))
		ft_error_rt(map_invalid, scene);
	cam->point = ato_xyz(arr[1], scene);
	cam->vector = ato_xyz(arr[2], scene);
	cam->fov = rt_atoi(arr[3], scene);
	if (cam->fov < 0 || cam->fov > 180)
		ft_error_rt(map_invalid, scene);
	new = ft_dlstnew(cam);
	if (!new)
		ft_error_rt(malloc_err, scene);
	ft_dlstadd(&scene->cam, new);
	split_free(arr);
}
