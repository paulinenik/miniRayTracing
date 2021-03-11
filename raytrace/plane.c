/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:05:13 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/11 23:06:37 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_plane(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		i;
	double		t;
	t_plane		*pl;
	t_list		*pl_list;

	pl_list = scene->pl;
	i = 1.0;
	while (pl_list)
	{
		pl = pl_list->content;
		if ((t = intersection_pl(o, v, pl)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = pl->color;
			pixel->n = pl->vector;
			pixel->id = PL;
			i = lighting(o, v, pixel, scene);
			pixel->color = apply_intensity(pixel->rgb, i);
		}
		pl_list = pl_list->next;
	}
}

double	intersection_pl(t_xyz o, t_xyz v, t_plane *pl)
{
	double t;
	double d;

	t = 0.0;
	d = -vect_scalar(pl->vector, pl->point);
	if (fabs(vect_scalar(v, pl->vector)) < 0.0000001)
		return (0);
	if (vect_scalar(v, pl->vector))
		t = -(vect_scalar(pl->vector, o) + d) / vect_scalar(v, pl->vector);
	if (t > 0.0001 && t < INFINITY)
		return (t);
	return (0);
}
