/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:24:46 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 16:26:48 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cam(char *line, t_scene scene)
{
	char **arr;

	arr = ft_split(line, ' ');
	// if (!arr)
	// 	printf("Malloc error");
	if (ft_strncmp(arr[0], "c", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	scene->cam = 
	scene->r.height = rt_atoi(arr[2]);
	if (scene->r.width <= 0 || scene->r.height <= 0)
	//"map error resolution corruped"
	// if (arr[4])
	// 	printf("map error extra chars\n");
	// free(arr)
}