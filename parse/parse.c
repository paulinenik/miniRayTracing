/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:15:08 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 02:25:14 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_scene(char *line, t_scene *scene)
{
	//if (ft_strnstr(line, "R", 1))
	//	parse_resolution(line, scene);
	//if (ft_strnstr(line, "A", 1))
	//	parse_ambient(line, scene);
	if (ft_strnstr(line, "c", 1))
		parse_cam(line, scene);
	//if (ft_strnstr(line, "l", 1))
	//	parse_light(line, scene);
	//if (ft_strnstr(line, "sp", 2))
	//	parse_sp(line, scene);
	//if (ft_strnstr(line, "pl", 2))
	//	parse_pl(line, scene);
	//if (ft_strnstr(line, "sq", 2))
	//	parse_sq(line, scene);
	if (ft_strnstr(line, "cy", 2))
		parse_cy(line, scene);
	if (ft_strnstr(line, "tr", 2))
		parse_tr(line, scene);
}

void	init_scene(t_scene **scene)
{
	*scene = (t_scene *)malloc(sizeof (t_scene));
	if (!(*scene))
		ft_error_rt(MALLOC_ERR, *scene);
	(*scene)->r.width = -1;
	(*scene)->r.height = -1;
	(*scene)->a.bright = 0;
	(*scene)->cam = NULL;
	(*scene)->light = NULL;
	(*scene)->sp = NULL;
	(*scene)->pl = NULL;
	(*scene)->sq = NULL;
	(*scene)->cy = NULL;
	(*scene)->tr = NULL;
}

void		parse(int fd)
{
	t_scene	*scene;
	char	*line;
	int		gnl;
	
	scene = NULL;
	init_scene(&scene);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (!(ft_strncmp("", line, ft_strlen(line))))
			continue;
		else
			get_scene(line, scene);
	}
	if (!gnl && !(ft_strncmp("", line, ft_strlen(line))))
		get_scene(line, scene);
	if (gnl == -1)
		ft_error_rt(READ_ERR, scene);
	// return scene or go further
	//printf("\n---RESOLUTION---\n");
	//printf("width is %d height is %d\n", scene->r.width, scene->r.height);
	printf("\n---AMBIENT---\n");
	printf("brigthness is %f\n", scene->a.bright);
	printf("red %d green %d blue %d", scene->a.color.red, scene->a.color.green, scene->a.color.blue);
}