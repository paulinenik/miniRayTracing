/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:02:27 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:14:43 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	rt_triangle(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		t;
	t_triangle	*tr;
	t_list		*tr_list;

	tr_list = scene->tr;
	while (tr_list)
	{
		tr = tr_list->content;
		if ((t = intersection_tr(o, v, tr)) && (t < pixel->t))
		{
			pixel->t = t;
			pixel->rgb = tr->color;
			pixel->n = tr->n;
			lighting(o, v, pixel, scene);
			pixel->color = rgb_to_int(pixel->rgb, pixel->i);
		}
		tr_list = tr_list->next;
	}
}

double	intersection_tr(t_xyz o, t_xyz d, t_triangle *tr)
{
	double			t;
	t_barycentric	coo;

	tr->ab = vect_direction(tr->a, tr->b);
	tr->bc = vect_direction(tr->c, tr->b);
	tr->n = cross_product(tr->ab, tr->bc);
	coo.det = dot_product(tr->ab, cross_product(d, tr->bc));
	if (fabs(coo.det) < EPSYLON)
		return (0);
	coo.tvec = vect_direction(o, tr->b);
	coo.u = dot_product(coo.tvec, cross_product(d, tr->bc)) / coo.det;
	if (coo.u < 0.0 || coo.u > 1.0)
		return (0);
	coo.qvec = cross_product(coo.tvec, tr->ab);
	coo.v = dot_product(d, coo.qvec) / coo.det;
	if (coo.v < EPSYLON || coo.v + coo.u > 0.99999)
		return (0);
	t = dot_product(tr->bc, coo.qvec) / coo.det;
	if (t > EPSYLON && t < INFINITY)
		return (t);
	return (0);
}
