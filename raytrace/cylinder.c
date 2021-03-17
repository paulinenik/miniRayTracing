/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:55:26 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/17 20:03:50 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		rt_cylinder(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		t;
	t_cylinder	*cy;
	t_list		*cy_list;

	cy_list = scene->cy;
	while (cy_list)
	{
		cy = cy_list->content;
		if ((t = intersection_cy(o, v, cy)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = cy->color;
			pixel->n = get_normal_cy(o, v, t, cy);
			pixel->id = CY;
			lighting(o, v, pixel, scene);
		}
		cy_list = cy_list->next;
	}
	pixel->color = rgb_to_int(pixel->rgb, pixel->i);
}

static int	check_point(double t, t_xyz v, t_cylinder *cy)
{
	double m;

	m = dot_product(v, cy->vector) * t * 0.99 + dot_product(cy->oc, cy->vector);
	if (m >= 0.0 && m <= cy->height)
		return (1);
	return (0);
}

static int	check_t(int f1, int f2, double t1, double t2)
{
	double closest;

	closest = 0;
	if (f1 && f2)
		closest = t1 > t2 ? t2 : t1;
	else if (f1)
		return (t1);
	else if (f2)
		return (t2);
	return (closest);
}

double		intersection_cy(t_xyz o, t_xyz v, t_cylinder *cy)
{
	t_eq	eq;
	int		f1;
	int		f2;

	f1 = 0;
	f2 = 0;
	cy->c = vect_direction(cy->point, vect_mult(cy->height / 2, cy->vector));
	cy->oc = vect_direction(o, cy->c);
	eq.a = dot_product(v, v) - pow(dot_product(v, cy->vector), 2);
	eq.b = 2.0 * (dot_product(cy->oc, v) - dot_product(v,
	cy->vector) * dot_product(cy->oc, cy->vector));
	eq.c = dot_product(cy->oc, cy->oc) - pow(dot_product(cy->oc,
	cy->vector), 2) - pow(cy->r, 2);
	eq.discr = eq.b * eq.b - 4.0 * eq.a * eq.c;
	if (eq.discr < 0)
		return (0);
	eq.x1 = (-eq.b + sqrt(eq.discr)) / (2.0 * eq.a);
	eq.x2 = (-eq.b - sqrt(eq.discr)) / (2.0 * eq.a);
	if (eq.x1 > 0.0 && eq.x1 < INFINITY)
		f1 = check_point(eq.x1, v, cy);
	if (eq.x2 > 0.0 && eq.x2 < INFINITY)
		f2 = check_point(eq.x2, v, cy);
	return (check_t(f1, f2, eq.x1, eq.x2));
}

t_xyz		get_normal_cy(t_xyz o, t_xyz v, double t, t_cylinder *cy)
{
	t_xyz	p;
	double	m;
	t_xyz	n;

	p = vect_sum(o, vect_mult(t * 0.99, v));
	m = dot_product(v, cy->vector) * t + dot_product(cy->oc, cy->vector);
	n = vect_direction(p, cy->c);
	n = vect_direction(n, vect_mult(m, cy->vector));
	return (normalize(n));
}
