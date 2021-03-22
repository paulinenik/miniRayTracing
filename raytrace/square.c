/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:39:22 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/19 20:34:05 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			rt_square(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
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
			pixel->n = sq->n;
			pixel->id = SQ;
			lighting(o, v, pixel, scene);
			pixel->color = rgb_to_int(pixel->rgb, pixel->i);
		}
		sq_list = sq_list->next;
	}
}

static t_xyz	rotate(t_square *sq, double x, double y)
{
	t_xyz	right;
	t_xyz	up;
	t_xyz	dot;

	right = normalize(cross_product((t_xyz){0.0, 1.0, 0.0}, sq->vect));
	up = normalize(cross_product(sq->vect, right));
	dot = vect_sum(sq->center, vect_mult(x, right));
	dot = vect_sum(dot, vect_mult(y, up));
	return (dot);
}

static void		make_triangle(t_square *sq, t_triangle *t1, t_triangle *t2)
{
	t_xyz	a;
	t_xyz	b;
	t_xyz	c;
	t_xyz	d;

	a = rotate(sq, sq->size / 2, sq->size / 2);
	b = rotate(sq, -sq->size / 2, sq->size / 2);
	c = rotate(sq, sq->size / 2, -sq->size / 2);
	d = rotate(sq, -sq->size / 2, -sq->size / 2);
	t1->a = a;
	t1->b = b;
	t1->c = c;
	t2->a = t1->b;
	t2->b = t1->c;
	t2->c = d;
	t1->color = sq->color;
	t2->color = sq->color;
}

double			intersection_sq(t_xyz o, t_xyz d, t_square *sq)
{
	t_triangle	abc;
	t_triangle	bcd;
	double		t;

	make_triangle(sq, &abc, &bcd);
	if ((t = intersection_tr(o, d, &abc)))
	{
		abc.ab = vect_direction(abc.a, abc.b);
		abc.bc = vect_direction(abc.c, abc.b);
		sq->n = normalize(cross_product(abc.ab, abc.bc));
		return (t);
	}
	else
	{
		bcd.ab = vect_direction(bcd.a, bcd.b);
		bcd.bc = vect_direction(bcd.c, bcd.b);
		sq->n = normalize(cross_product(bcd.ab, bcd.bc));
	}
	return (intersection_tr(o, d, &bcd));
}
