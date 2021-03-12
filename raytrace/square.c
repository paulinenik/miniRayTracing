/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:39:22 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/12 21:56:55 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_square(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		t;
	t_square	*sq;
	t_list		*sq_list;

	sq_list = scene->sq;
	while (sq_list)
	{
		sq = sq_list->content;
		if ((t = intersection_sq(o, v, sq)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = sq->color;
			pixel->n = sq->vect;
			pixel->id = SQ;
			lighting(o, v, pixel, scene);
			pixel->color = rgb_to_int(pixel->rgb, pixel->i);
		}
		sq_list = sq_list->next;
	}
}

double	intersection_sq(t_xyz o, t_xyz d, t_square *sq)
{
	double	halfsize;
	double	t;
	double	pl_d;
	t_xyz	p;
	t_xyz	v;

	t = 0.0;
	halfsize = sq->sidesize / 4;
	pl_d = -dot_product(sq->vect, sq->center);
	if (fabs(dot_product(d, sq->vect)) < 0.001)
		return (0);
	if (dot_product(d, sq->vect))
		t = -(dot_product(sq->vect, o) + pl_d) / dot_product(d, sq->vect);
	if (t > 0.0 && t < INFINITY)
	{
		p = vect_sum(o, vect_mult(t, d));
		v = vect_direction(p, sq->center);
		if (fabs(v.x) <= halfsize && fabs(v.y) <= halfsize && \
		fabs(v.z) <= halfsize)
			return (t);
	}
	return (0);
}
