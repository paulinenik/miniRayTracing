/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:15:08 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 18:28:10 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void test(t_scene *scene)
	{
		t_light *l;
		t_sphere *sp;
		t_plane *pl;
		t_square *sq;
		t_cylinder * cy;
		t_triangle *tr;

		printf("\n---RESOLUTION---\n");
		printf("width is %d height is %d\n", scene->r.width, scene->r.height);
		printf("\n---AMBIENT---\n");
		printf("brigthness is %f\n", scene->a.bright);
		printf("red %d green %d blue %d\n", scene->a.color.red, scene->a.color.green, scene->a.color.blue);
		printf("\n---CAMERA---\n");
		printf("point x %f y %f z %f\n", scene->cam->data->point.x, scene->cam->data->point.y, scene->cam->data->point.z);
		printf("vector x %f y %f z %f\n", scene->cam->data->vector.x, scene->cam->data->vector.y, scene->cam->data->vector.z);
		printf("fov %d\n", scene->cam->data->fov);
		printf("\n---CAMERA 2---\n");
		scene->cam = scene->cam->next;
		printf("point x %f y %f z %f\n", scene->cam->data->point.x, scene->cam->data->point.y, scene->cam->data->point.z);
		printf("vector x %f y %f z %f\n", scene->cam->data->vector.x, scene->cam->data->vector.y, scene->cam->data->vector.z);
		printf("fov %d\n", scene->cam->data->fov);
		printf("\n---LIGHT POINT---\n");
		l = (t_light *)scene->light->content;
		printf("point x %f y %f z %f\n", l->point.x, l->point.y, l->point.z);
		printf("brightness is %f\n", l->bright);
		printf("red %d green %d blue %d\n", l->color.red, l->color.green, l->color.blue);
		printf("\n---SPHERE---\n");
		sp = (t_sphere *)scene->sp->content;
		printf("point x %f y %f z %f\n", sp->center.x, sp->center.y, sp->center.z);
		printf("diameter is %f\n", sp->diameter);
		printf("red %d green %d blue %d\n", sp->color.red, sp->color.green, sp->color.blue);
		printf("\n---SPHERE 2---\n");
		sp = (t_sphere *)scene->sp->next->content;
		printf("point x %f y %f z %f\n", sp->center.x, sp->center.y, sp->center.z);
		printf("diameter is %f\n", sp->diameter);
		printf("red %d green %d blue %d\n", sp->color.red, sp->color.green, sp->color.blue);
		printf("\n---PLANE---\n");
		pl = (t_plane *)scene->pl->content;
		printf("point x %f y %f z %f\n", pl->point.x, pl->point.y, pl->point.z);
		printf("vector x %f y %f z %f\n", pl->vector.x, pl->vector.y, pl->vector.z);
		printf("red %d green %d blue %d\n", pl->color.red, pl->color.green, pl->color.blue);
		printf("\n---SQUARE---\n");
		sq = (t_square *)scene->sq->content;
		printf("point x %f y %f z %f\n", sq->center.x, sq->center.y, sq->center.z);
		printf("vector x %f y %f z %f\n", sq->vector.x, sq->vector.y, sq->vector.z);
		printf("sidesize %f\n", sq->sidesize);
		printf("red %d green %d blue %d\n", sq->color.red, sq->color.green, sq->color.blue);
		printf("\n---CYLINDER---\n");
		cy = (t_cylinder *)scene->cy->content;
		printf("point x %f y %f z %f\n", cy->point.x, cy->point.y, cy->point.z);
		printf("vector x %f y %f z %f\n", cy->vector.x, cy->vector.y, cy->vector.z);
		printf("diameter is %f height is %f\n", cy->diameter, cy->height);
		printf("red %d green %d blue %d\n", cy->color.red, cy->color.green, cy->color.blue);
		printf("\n---TRIANGLE--\n");
		tr = (t_triangle *)scene->tr->content;
		printf("point x %f y %f z %f\n", tr->p1.x, tr->p1.y, tr->p1.z);
		printf("point x %f y %f z %f\n", tr->p2.x, tr->p2.y, tr->p2.z);
		printf("point x %f y %f z %f\n", tr->p3.x, tr->p3.y, tr->p3.z);
		printf("red %d green %d blue %d\n", tr->color.red, tr->color.green, tr->color.blue);
	}
	
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
		{
			get_scene(line, scene);
			free(line);
			line = NULL;
		}
	}
	if (gnl == 0)
		get_scene(line, scene);
	free(line);
	line = NULL;
	if (gnl == -1)
		ft_error_rt(READ_ERR, scene);
	// return scene or go further
	test(scene);
}
