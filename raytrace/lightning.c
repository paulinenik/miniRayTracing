/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:31:33 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/27 20:15:21 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	lighting(t_xyz o, t_xyz v, t_pixel *pixel, t_xyz c, t_scene *scene)
{
	t_xyz p;
	t_xyz n;
	t_xyz ld;
	double nl;
	t_light	*light;
	t_list	*l;
	double i;

	p = vect_sum(o, vect_mult(pixel->t, v)); 
	n = vect_direction(p, c);
	n = vect_norm(vlen(n), n);
	l = (t_list *)scene->light;
	i = scene->a.bright;

	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
		{
			nl = vect_scalar(n, ld);
			if (nl > 0.0)
				i += light->bright * nl / (vlen(n) * vlen(ld));
			if (i > 1.0)
				return (1.0);
		}
		l = l->next;
	}
	return (i);
}
double	lighting_pl(t_xyz o, t_xyz v, t_pixel *pixel, t_plane *pl, t_scene *scene)
{
	t_xyz p;
	t_xyz n;
	t_xyz ld;
	double nl;
	t_light	*light;
	t_list	*l;
	double i;

	p = vect_sum(o, vect_mult(pixel->t, v)); 
	n = pl->vector;
	l = (t_list *)scene->light;
	i = scene->a.bright;

	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
		{
			nl = vect_scalar(n, ld);
			if (nl > 0.0)
				i += light->bright * nl / (vlen(n) * vlen(ld));
			if (i > 1.0)
				return (1.0);
		}
		l = l->next;
	}
	return (i);
}

double	intersection_shadow(t_xyz o, t_xyz v, t_scene *scene)
{	
	int	i;

	i = 0;
	if (shadow_sp(o, v, scene->sp))
		i++;	
	else if (shadow_pl(o, v, scene->pl))
		i++;	
	// else if (shadow_cy(o, v, scene->cy))
	// 	i++;	
	// else if (shadow_tr(o, v, scene->tr))
	// 	i++;	
	// else if (shadow_sq(o, v, scene->sq))
	// 	i++;
	return(i);
}

double	shadow_sp(t_xyz o, t_xyz v, t_list *sphere)
{
	t_xyz oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;
	double t1;
	double t2;
	t_sphere	*sp;
	t_list		*sp_list;
	sp_list = sphere;

	while(sp_list)
	{	
		sp = sp_list->content;
		oc = vect_direction(o, sp->center);
		k1 = vect_scalar(v, v);
		k2 = 2.0 * vect_scalar(oc, v);
		k3 = vect_scalar(oc, oc) - sp->r;
		discr = k2 * k2 - 4.0 * k1 * k3;
		if (discr < 0)
		{
			sp_list = sp_list->next;
			continue;
		}
		t1 = (-k2 + sqrt(discr)) / (2.0 * k1);
		t2 = (-k2 - sqrt(discr)) / (2.0 * k1);
		if (t1 > 0.001 && t1 < 1.0)
			return (t1);
		if (t2 > 0.001 && t2 < 1.0)
			return (t2);
		sp_list = sp_list->next;
	}
	return (0);
}

double	shadow_pl(t_xyz o, t_xyz v, t_list *plane)
{
	double	t;
	double	d;
	t_plane	*pl;
	t_list	*pl_list;
	pl_list = plane;

	while(pl_list)
	{	
		pl = pl_list->content;
		d = -vect_scalar(pl->vector, pl->point);
		if (fabs(vect_scalar(v, pl->vector)) < 0.0000001)
		{
			pl_list = pl_list->next;
			continue;
		}
		if (vect_scalar(v, pl->vector))
			t = -(vect_scalar(pl->vector, o) + d) / vect_scalar(v, pl->vector);
		if (t > 0.0001 && t < 1.0)
			return (t);
		pl_list = pl_list->next;
	}
	return (0);
}