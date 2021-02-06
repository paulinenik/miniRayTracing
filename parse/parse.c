/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:15:08 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/05 22:57:15 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int	parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		gnl;
	init_scene(scene);
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp("", line, ft_strlen(line))))
			continue;
		else
			get_scene(line);
	}
	
}