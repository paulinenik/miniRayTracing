/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:02:27 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/09 20:56:56 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_triangle(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		i;
	double		t;
	t_triangle		*tr;
	t_list		*tr_list;

	tr_list = scene->tr;
	i = 1.0;
	while(tr_list)
	{
		tr = tr_list->content;
		if ((t = intersection_tr(o, v, tr)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = tr->color;
			i = lighting_tr(o, v, pixel, tr, scene);
			pixel->color = apply_intensity(pixel->rgb, i);
		}
		tr_list = tr_list->next;
	}	
}

double	intersection_tr(t_xyz o, t_xyz d, t_triangle *tr)
{
	t_xyz ed1;
	t_xyz ed2;
	t_xyz tvec;
	t_xyz qvec;
	double det;
	double u;
	double v;
	double t;

	ed1 = vect_direction(tr->p1, tr->p2);
	ed2 = vect_direction(tr->p3, tr->p2);
	tr->n = vector_prod(ed1, ed2);
	det = vect_scalar(ed1, vector_prod(d, ed2));
	if (fabs(det) < 0.000001)
		return(0);
	tvec = vect_direction(o, tr->p2);
	u = vect_scalar(tvec, vector_prod(d, ed2)) / det;
	if (u < 0.0 || u > 1.0)
		return (0);
	qvec = vector_prod(tvec, ed1);
	v = vect_scalar(d, qvec) / det;
	if (v < 0.0 || v + u > 1.0)
		return(0);
	t = vect_scalar(ed2, qvec) / det;
	if (t > 0.0 && t < INFINITY)
		return (t);
	return (0);
}