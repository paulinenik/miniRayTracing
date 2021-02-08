/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:17:20 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 16:26:28 by rgordon          ###   ########.fr       */
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
	scene->a.bright = ft_atof(arr[1]);
	if (scene->a.bright < 0 || scene->a.bright > 1)
		printf("map error brightnes");
	scene->a.color = atorgb(arr[2]);
	// if (arr[3])
	// 	printf("map error extra chars\n");
	// free(arr)
	printf("brigthness is %f\n", scene->a.brightness);
	printf("red %d green %d blue %d", scene->a.color.red, scene->a.color.green, scene->a.color.blue);
}
