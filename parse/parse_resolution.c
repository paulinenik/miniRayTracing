/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:13:41 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/07 22:02:44 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char **arr;

	arr = ft_split(line, ' ');
	// if (!arr)
	// 	printf("Malloc error");
	if (ft_strncmp(arr[0], "R", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	scene->r.width = rt_atoi(arr[1]);
	scene->r.height = rt_atoi(arr[2]);
	if (scene->r.width <= 0 || scene->r.height <= 0)
	//"map error resolution corruped"
	// if (arr[3])
	// 	printf("map error extra chars\n");
	printf("width is %d height is %d", scene->r.width, scene->r.height);
}

int		main(void)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof (t_scene));
	parse_resolution("Rs 19f20 1080 kd", scene);
	return (0);
}