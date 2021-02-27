/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:02:54 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/27 19:33:59 by rgordon          ###   ########.fr       */
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
	i = 1.0;
	while(sp_list)
	{
		sp = sp_list->content;
		if (!sp->r)
			sp->r = pow(sp->diameter / 2, 2);
		if ((t = intersection_sp(o, v, sp)) && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = sp->color;
			i = lighting(o, v, pixel, sp->center, scene);
		}
		sp_list = sp_list->next;
	}
	pixel->color = lightcolor(pixel->rgb, i);	
}

double	intersection_sp(t_xyz o, t_xyz v, t_sphere *sp)
{
	t_xyz oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;
	double t1;
	double t2;

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

// double	lighting(t_xyz o, t_xyz v, t_list *l, double t, t_xyz c, double a, t_list *sp)
// {
// 	t_xyz p;
// 	t_xyz n;
// 	t_xyz ld;
// 	double nl;
// 	t_light	*light;
// 	t_list	*l2;
// 	double i;

// 	i = a;
// 	v = vect_mult(t, v);
// 	p = vect_sum(o, v);
// 	n = vect_direction(p, c);
// 	n = vect_norm(vlen(n), n);
// 	l2 = l;

// 	while (l2)
// 	{
// 		light = l2->content;
// 		ld = vect_direction(light->point, p);
// 		if (!intersection_shadow(p, ld, sp))
// 		{
// 			nl = vect_scalar(n, ld);
// 			if (nl > 0.0)
// 				i += light->bright * nl / (vlen(n) * vlen(ld));
// 			if (i > 1.0)
// 				return (1.0);
// 		}
// 		l2 = l2->next;
// 	}
// 	return (i);
// }

// double	intersection_shadow(t_xyz o, t_xyz v, t_list *sphere)
// {
// 	t_xyz oc;
// 	double	k1;
// 	double	k2;
// 	double	k3;
// 	double	discr;
// 	double t1;
// 	double t2;
// 	t_sphere	*sp;
// 	t_list		*sp_list;
// 	sp_list = sphere;

// 	while(sp_list)
// 	{	
// 		sp = sp_list->content;
// 		oc = vect_direction(o, sp->center);
// 		k1 = vect_scalar(v, v);
// 		k2 = 2.0 * vect_scalar(oc, v);
// 		k3 = vect_scalar(oc, oc) - sp->r;
// 		discr = k2 * k2 - 4.0 * k1 * k3;
// 		if (discr < 0)
// 		{
// 			sp_list = sp_list->next;
// 			continue;
// 		}
// 		t1 = (-k2 + sqrt(discr)) / (2.0 * k1);
// 		t2 = (-k2 - sqrt(discr)) / (2.0 * k1);
// 		if (t1 > 0.001 && t1 < 1.0)
// 			return (t1);
// 		if (t2 > 0.001 && t2 < 1.0)
// 			return (t2);
// 		sp_list = sp_list->next;
// 	}
// 	return (0);
// }