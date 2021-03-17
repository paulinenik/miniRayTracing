/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:39:22 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/17 18:50:27 by rgordon          ###   ########.fr       */
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

// double	intersection_sq(t_xyz o, t_xyz d, t_square *sq)
// {
// 	double	halfsize;
// 	double	t;
// 	double	pl_d;
// 	t_xyz	p;
// 	t_xyz	v;

// 	t = 0.0;
// 	halfsize = sq->sidesize / 4;
// 	pl_d = -dot_product(sq->vect, sq->center);
// 	if (fabs(dot_product(d, sq->vect)) < 0.001)
// 		return (0);
// 	if (dot_product(d, sq->vect))
// 		t = -(dot_product(sq->vect, o) + pl_d) / dot_product(d, sq->vect);
// 	if (t > 0.0 && t < INFINITY)
// 	{
// 		p = vect_sum(o, vect_mult(t * 0.99, d));
// 		v = vect_direction(p, sq->center);
// 		if (fabs(v.x) <= halfsize && fabs(v.y) <= halfsize && \
// 		fabs(v.z) <= halfsize)
// 			return (t);
// 	}
// 	return (0);
// }


static t_xyz	rotate(t_xyz dot, t_xyz orientation)
{
	dot.y = dot.y * cos(orientation.x) - dot.z * sin(orientation.x);
	dot.z = dot.y * sin(orientation.x) + dot.z * cos(orientation.x);
	dot.x = dot.x * cos(orientation.y) + dot.z * sin(orientation.y);
	dot.z = -(dot.x * sin(orientation.y)) + dot.z * cos(orientation.y);
	dot.x = dot.x * cos(orientation.z) - dot.y * sin(orientation.z);
	dot.y = dot.x * sin(orientation.z) + dot.y * cos(orientation.z);
	return (dot);
}

static void	make_triangle(t_square *sq, t_triangle *t1, t_triangle *t2)
{
	t_xyz	a;
	t_xyz	b;
	t_xyz	c;
	t_xyz	d;

	a = vect_sum(sq->center, (t_xyz){sq->size/2, sq->size/2, 0});
	b = vect_sum(sq->center, (t_xyz){-sq->size/2, sq->size/2, 0});
	c = vect_sum(sq->center, (t_xyz){sq->size/2, -sq->size/2, 0});
	d = vect_sum(sq->center, (t_xyz){-sq->size/2, -sq->size/2, 0});
	t1->a = rotate(a, sq->vect);
	t1->b = rotate(b, sq->vect);
	t1->c = rotate(c, sq->vect);
	t2->a = t1->b;
	t2->b = t1->c;
	t2->c = rotate(d, sq->vect);
	t1->color = sq->color;
	t2->color = sq->color;
}

double	intersection_sq(t_xyz o, t_xyz d, t_square *sq)
{
	t_triangle	abc;
	t_triangle	bcd;
	double	t;

	make_triangle(sq, &abc, &bcd);
	if ((t = intersection_tr(o, d, &abc)))
		return (t);
	else return (intersection_tr(o, d, &bcd));
	// t = 0.0;
	// halfsize = sq->sidesize / 4;
	// pl_d = -dot_product(sq->vect, sq->center);
	// if (fabs(dot_product(d, sq->vect)) < 0.001)
	// 	return (0);
	// if (dot_product(d, sq->vect))
	// 	t = -(dot_product(sq->vect, o) + pl_d) / dot_product(d, sq->vect);
	// if (t > 0.0 && t < INFINITY)
	// {
	// 	p = vect_sum(o, vect_mult(t * 0.99, d));
	// 	v = vect_direction(p, sq->center);
	// 	if (fabs(v.x) <= halfsize && fabs(v.y) <= halfsize && \
	// 	fabs(v.z) <= halfsize)
	// 		return (t);
	// }
	// return (0);
}