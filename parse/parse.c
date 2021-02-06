/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:15:08 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/06 17:11:31 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_scene(char *line, t_scene *scene)
{
	if (ft_strnstr(line, "R", 1))
		parse_resolution(line, scene);
	if (ft_strnstr(line, "A", 1))
		parse_ambient(line, scene);
	if (ft_strnstr(line, "c", 1))
		parse_cam(line, scene);
	if (ft_strnstr(line, "l", 1))
		parse_light(line, scene);
	if (ft_strnstr(line, "sp", 2))
		parse_sp(line, scene);
	if (ft_strnstr(line, "pl", 2))
		parse_pl(line, scene);
	if (ft_strnstr(line, "sq", 2))
		parse_sq(line, scene);
	if (ft_strnstr(line, "cy", 2))
		parse_cy(line, scene);
	if (ft_strnstr(line, "tr", 2))
		parse_tr(line, scene);
}

void	init_scene(t_scene *scene)
{
	scene = (t_scene *)malloc(sizeof t_scene);
	if (!scene)
		// malloc error
	scene->resolution.width = -1;
	scene->resolution.height = -1;
	scene->amb_light.brightness = 0;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->sq = NULL;
	scene->cy = NULL;
	scene->tr = NULL;
}

int		parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		gnl;
	init_scene(scene);
	while (gnl = get_next_line(fd, &line))
	{
		if (!(ft_strncmp("", line, ft_strlen(line))))
			continue;
		else
			get_scene(line, scene);
	}
	if (!gnl && !(ft_strncmp("", line, ft_strlen(line))))
		get_scene(line, scene);
	if (gnl == -1)
		// reading error
	// return scene or go further
}