/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:05:13 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/12 21:56:55 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_plane(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		t;
	t_plane		*pl;
	t_list		*pl_list;

	pl_list = scene->pl;
	while (pl_list)
	{
		pl = pl_list->content;
		if ((t = intersection_pl(o, v, pl)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = pl->color;
			pixel->n = pl->vector;
			pixel->id = PL;
			lighting(o, v, pixel, scene);
			pixel->color = rgb_to_int(pixel->rgb, pixel->i);
		}
		pl_list = pl_list->next;
	}
}

double	intersection_pl(t_xyz o, t_xyz v, t_plane *pl)
{
	double t;
	double d;

	t = 0.0;
	d = -dot_product(pl->vector, pl->point);
	if (fabs(dot_product(v, pl->vector)) < 0.001)
		return (0);
	if (dot_product(v, pl->vector))
		t = -(dot_product(pl->vector, o) + d) / dot_product(v, pl->vector);
	if (t > 0.0 && t < INFINITY)
		return (t);
	return (0);
}
