/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:24:46 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 02:23:42 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cam(char *line, t_scene *scene)
{
	t_camera *cam;
	t_dlist	*new;
	char	**arr;

	arr = ft_split(line, ' ');
	cam = (t_camera *)malloc(sizeof (t_camera));
	if (!cam || !arr)
		ft_error_rt(MALLOC_ERR, scene);
	if (ft_strncmp(arr[0], "c", ft_strlen(arr[0])))
		ft_error_rt(MAP_INVALID, scene);
	cam->point = ato_xyz(arr[1], scene);
	cam->vector = ato_xyz(arr[2], scene);
	cam->fov = rt_atoi(&arr[3], scene);
	if (arr[4])
		ft_error_rt(MAP_INVALID, scene);
	new = ft_dlstnew(cam);
	if (!new)
		ft_error_rt(MALLOC_ERR, scene);
	ft_dlstadd(&scene->cam, new);
	//free arr
}