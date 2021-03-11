/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:39:22 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/11 16:00:29 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_square(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		i;
	double		t;
	t_square		*sq;
	t_list		*sq_list;

	sq_list = scene->sq;
	i = 1.0;
	while(sq_list)
	{
		sq = sq_list->content;
		if ((t = intersection_tr(o, v, sq)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = sq->color;
			i = lighting_sq(o, v, pixel, sq, scene);
			pixel->color = apply_intensity(pixel->rgb, i);
		}
		sq_list = sq_list->next;
	}	
}

double	intersection_sq(t_xyz o, t_xyz d, t_square *sq)
{
	double	halfsize;
	double t;
	double plane_d;
	t_xyz	p;
	t_xyz	v;

	t = 0.0;
	halfsize = sq->sidesize / 2;
	plane_d = -vect_scalar(sq->vector, sq->center);
	if (fabs(vect_scalar(v, sq->vector)) < 0.0000001)
		return(0);
	if (vect_scalar(v, sq->vector))
		t = -(vect_scalar(sq->vector, o) + plane_d) / vect_scalar(v, sq->vector);
	if (t < 0.0001 || t > INFINITY)
		return(0);
	p = vect_sum(o, vect_mult(t, d));
	v = vect_direction(p, sq->center);
	if (fabs(v.x) <= halfsize && fabs(v.y) <= halfsize && fabs(v.z) <= halfsize)
		return (t);
	return (0);
}