/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:24:46 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 18:23:02 by rgordon          ###   ########.fr       */
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
	//malloc error
	if (ft_strncmp(arr[0], "cam", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	cam->point = ato_xyz(arr[1]);
	cam->vector = ato_xyz(arr[2]);
	cam->fov = rt_atoi(arr[3]);
	// if (arr[4])
	// 	printf("map error extra chars\n");
	new = ft_dlstnew(cam);
	if (!new)
	// malloc error
	ft_dlstadd(&scene->cam, new);
	//free arr
}