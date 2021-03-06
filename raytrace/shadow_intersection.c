/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:39:14 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:13:27 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	shadow_sp(t_xyz o, t_xyz v, t_list *sphere)
{
	t_eq		eq;
	t_sphere	*sp;
	t_list		*sp_list;

	sp_list = sphere;
	while (sp_list)
	{
		sp = sp_list->content;
		sp->oc = vect_direction(o, sp->center);
		eq.a = dot_product(v, v);
		eq.b = 2.0 * dot_product(sp->oc, v);
		eq.c = dot_product(sp->oc, sp->oc) - pow(sp->r, 2);
		eq.discr = eq.b * eq.b - 4.0 * eq.a * eq.c;
		if (eq.discr >= 0)
		{
			eq.x1 = (-eq.b + sqrt(eq.discr)) / (2.0 * eq.a);
			eq.x2 = (-eq.b - sqrt(eq.discr)) / (2.0 * eq.a);
			if (eq.x1 > EPSYLON && eq.x1 < 0.999999)
				return (eq.x1);
			if (eq.x2 > EPSYLON && eq.x2 < 0.999999)
				return (eq.x2);
		}
		sp_list = sp_list->next;
	}
	return (0);
}

double	shadow_pl(t_xyz o, t_xyz d, t_list *plane)
{
	double	t;
	t_plane	*pl;
	t_list	*pl_list;

	pl_list = plane;
	while (pl_list)
	{
		pl = pl_list->content;
		t = intersection_pl(o, d, pl);
		if (t > EPSYLON && t < 0.999999)
			return (t);
		pl_list = pl_list->next;
	}
	return (0);
}

double	shadow_tr(t_xyz o, t_xyz d, t_list *triangle)
{
	double			t;
	t_triangle		*tr;
	t_list			*tr_list;

	tr_list = triangle;
	while (tr_list)
	{
		tr = tr_list->content;
		t = intersection_tr(o, d, tr);
		if (t > EPSYLON && t < 0.999999)
			return (t);
		tr_list = tr_list->next;
	}
	return (0);
}

double	shadow_sq(t_xyz o, t_xyz d, t_list *square)
{
	double		t;
	t_square	*sq;
	t_list		*sq_list;

	sq_list = square;
	while (sq_list)
	{
		sq = sq_list->content;
		t = intersection_sq(o, d, sq);
		if (t > EPSYLON && t < 0.999999)
			return (t);
		sq_list = sq_list->next;
	}
	return (0);
}

double	shadow_cy(t_xyz o, t_xyz d, t_list *cylinder)
{
	double		t;
	t_cylinder	*cy;
	t_list		*cy_list;

	cy_list = cylinder;
	while (cy_list)
	{
		cy = cy_list->content;
		t = intersection_cy(o, d, cy);
		if (t > EPSYLON && t < 0.999999)
			return (t);
		cy_list = cy_list->next;
	}
	return (0);
}
