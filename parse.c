/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:15:08 by rgordon           #+#    #+#             */
/*   Updated: 2021/01/31 21:07:54 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse(char *map)
{
	t_scene		scene;
	t_alight	amibent;
	
	if (*map == 'R')
	{
		map++;
		get_xyz(&scene, &map);
	}
	while(*map == '\n')
		map++;
	if (*map == 'A')
	{
		map++;
		amibent.ratio = atof(&map);
		get_color(&ambient, &map);
	}
	parse_camnlight(&map);
	parse_objects(map);
	//обработать камеры и свет
}

//float	ft_atof(char **map);
//int	get_color(void *data, char **map);
//int	get_xyz(void *data, char **map);