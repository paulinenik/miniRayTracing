/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:15:08 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:09:43 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

void	get_scene(char *line, t_scene *scene)
{
	if (ft_strnstr(line, "R", 1))
		parse_resolution(line, scene);
	if (ft_strnstr(line, "A", 1))
		parse_ambient(line, scene);
	if (ft_strnstr(line, "c ", 2))
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

t_scene	*init_scene(void)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		ft_error_rt(malloc_err, scene);
	scene->r.height = -1;
	scene->r.width = -1;
	scene->a.bright = -1;
	scene->cam = NULL;
	scene->light = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->sq = NULL;
	scene->cy = NULL;
	scene->tr = NULL;
	return (scene);
}

void	parse(int fd, int save, char *name)
{
	t_scene	*scene;
	char	*line;
	int		gnl;

	scene = NULL;
	line = NULL;
	scene = init_scene();
	while ((gnl = get_next_line(fd, &line)))
	{
		if (ft_strncmp("", line, ft_strlen(line)))
			get_scene(line, scene);
		free(line);
		line = NULL;
	}
	if (gnl == 0)
		get_scene(line, scene);
	free(line);
	line = NULL;
	close(fd);
	if (gnl == -1)
		ft_error_rt(read_err, scene);
	if (save)
		create_bmp(name, scene);
	else
		init_img(scene);
}
