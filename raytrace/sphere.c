/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:02:54 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/11 23:06:23 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_sphere(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		i;
	double		t;
	t_sphere	*sp;
	t_list		*sp_list;

	sp_list = scene->sp;
	while (sp_list)
	{	
		sp = sp_list->content;
		if (!sp->r)
			sp->r = pow(sp->diameter / 2, 2);
		if ((t = intersection_sp(o, v, sp)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = sp->color;
			pixel->n = get_normal_sp(o, v, t, sp->center);
			pixel->id = SP;
			i = lighting(o, v, pixel, scene);
		}
		sp_list = sp_list->next;
	}
	pixel->color = apply_intensity(pixel->rgb, i);
}

double	intersection_sp(t_xyz o, t_xyz v, t_sphere *sp)
{
	t_xyz	oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;
	double	t1;
	double	t2;

	oc = vect_direction(o, sp->center);
	k1 = vect_scalar(v, v);
	k2 = 2.0 * vect_scalar(oc, v);
	k3 = vect_scalar(oc, oc) - sp->r;
	discr = k2 * k2 - 4.0 * k1 * k3;
	if (discr < 0)
		return (0);
	t1 = (-k2 + sqrt(discr)) / (2.0 * k1);
	t2 = (-k2 - sqrt(discr)) / (2.0 * k1);
	if (t1 <= t2 && t1 > 0.0 && t1 < INFINITY)
		return (t1);
	if (t2 > 0.0 && t2 < INFINITY)
		return (t2);
	return (0);
}

t_xyz	get_normal_sp(t_xyz o, t_xyz v, double t, t_xyz c)
{
	t_xyz p;
	t_xyz n;

	p = vect_sum(o, vect_mult(t, v));
	n = vect_direction(p, c);
	n = vect_norm(vlen(n), n);
	return (n);
}