/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:17:20 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/06 18:22:33 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_ambient(char *line, t_scene *scene)
{
	char **arr;

	arr = ft_split(line, ' ');
	// if (!arr)
	// 	printf("Malloc error");
	if (ft_strncmp(arr[0], "A", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	scene->a.brightness = ft_atof(arr[1]);
	scene->a.rgb = ft_atorgb(arr[2]);
	// if (arr[3])
	// 	printf("map error extra chars\n");
	printf("width is %d height is %d", scene->a.brightness, scene->a.rgb);
}

int		main(void)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof (t_scene));
	parse_resolution("Rs 19f20 1080 kd", scene);
	return (0);
}