/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:02:54 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/12 21:56:55 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_sphere(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		t;
	t_sphere	*sp;
	t_list		*sp_list;

	sp_list = scene->sp;
	while (sp_list)
	{
		sp = sp_list->content;
		if ((t = intersection_sp(o, v, sp)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = sp->color;
			pixel->n = get_normal_sp(o, v, t, sp->center);
			pixel->id = SP;
			lighting(o, v, pixel, scene);
		}
		sp_list = sp_list->next;
	}
	pixel->color = rgb_to_int(pixel->rgb, pixel->i);
}

double	intersection_sp(t_xyz o, t_xyz v, t_sphere *sp)
{
	t_eq	eq;

	sp->oc = vect_direction(o, sp->center);
	eq.a = dot_product(v, v);
	eq.b = 2.0 * dot_product(sp->oc, v);
	eq.c = dot_product(sp->oc, sp->oc) - pow(sp->r, 2);
	eq.discr = eq.b * eq.b - 4.0 * eq.a * eq.c;
	if (eq.discr < 0)
		return (0);
	eq.x1 = (-eq.b + sqrt(eq.discr)) / (2.0 * eq.a);
	eq.x2 = (-eq.b - sqrt(eq.discr)) / (2.0 * eq.a);
	if (eq.x1 <= eq.x2 && eq.x1 > 0.0 && eq.x1 < INFINITY)
		return (eq.x1);
	if (eq.x2 > 0.0 && eq.x2 < INFINITY)
		return (eq.x2);
	return (0);
}

t_xyz	get_normal_sp(t_xyz o, t_xyz v, double t, t_xyz c)
{
	t_xyz p;
	t_xyz n;

	p = vect_sum(o, vect_mult(t, v));
	n = vect_direction(p, c);
	return (normalize(n));
}
