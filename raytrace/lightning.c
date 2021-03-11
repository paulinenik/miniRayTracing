/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:31:33 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/11 16:12:09 by rgordon          ###   ########.fr       */
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
	pixel->rgb.red = pixel->rgb.red * i;
	pixel->rgb.green = pixel->rgb.green * i;
	pixel->rgb.blue = pixel->rgb.blue * i;
	pixel->rgb = lightcolor(pixel->rgb, scene->a.color, i);

	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
		{
			nl = vect_scalar(n, ld);
			if (nl >= 0.0)
			{
				i += light->bright * nl / (vlen(n) * vlen(ld));
				pixel->rgb = lightcolor(pixel->rgb, light->color, light->bright * nl / (vlen(n) * vlen(ld)));
			}
		}
		l = l->next;
	}
	if (i > 1.0)
		return (1.0);
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
	pixel->rgb.red = pixel->rgb.red * i;
	pixel->rgb.green = pixel->rgb.green * i;
	pixel->rgb.blue = pixel->rgb.blue * i;
	pixel->rgb = lightcolor(pixel->rgb, scene->a.color, i);

	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
		{
			nl = vect_scalar(n, ld);
			if (nl < 0.0)
				nl *= -1.0;
			if (nl > 0.0)
			{
				i += light->bright * nl / (vlen(n) * vlen(ld));
				pixel->rgb = lightcolor(pixel->rgb, light->color, light->bright * nl / (vlen(n) * vlen(ld)));
			}
		}
		l = l->next;
	}
	if (i > 1.0)
		return (1.0);
	return (i);
}
double	lighting_tr(t_xyz o, t_xyz v, t_pixel *pixel, t_triangle *tr, t_scene *scene)
{
	t_xyz p;
	t_xyz n;
	t_xyz ld;
	double nl;
	t_light	*light;
	t_list	*l;
	double i;

	p = vect_sum(o, vect_mult(pixel->t, v)); 
	n = tr->n;
	n = vect_norm(vlen(n), n);
	l = (t_list *)scene->light;
	i = scene->a.bright;
	pixel->rgb.red = pixel->rgb.red * i;
	pixel->rgb.green = pixel->rgb.green * i;
	pixel->rgb.blue = pixel->rgb.blue * i;
	pixel->rgb = lightcolor(pixel->rgb, scene->a.color, i);

	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
		{
			nl = vect_scalar(n, ld);
			if (nl < 0.0)
				nl *= -1.0;
			if (nl >= 0.0)
			{
				i += light->bright * nl / (vlen(n) * vlen(ld));
				pixel->rgb = lightcolor(pixel->rgb, light->color, light->bright * nl / (vlen(n) * vlen(ld)));
			}
		}
		l = l->next;
	}
	if (i > 1.0)
		return (1.0);
	// printf("%f\n", i);
	return (i);
}

double	lighting_sq(t_xyz o, t_xyz v, t_pixel *pixel, t_triangle sq, t_scene *scene)
{
	t_xyz p;
	t_xyz n;
	t_xyz ld;
	double nl;
	t_light	*light;
	t_list	*l;
	double i;

	p = vect_sum(o, vect_mult(pixel->t, v)); 
	n = sq->vect;
	n = vect_norm(vlen(n), n);
	l = (t_list *)scene->light;
	i = scene->a.bright;
	pixel->rgb.red = pixel->rgb.red * i;
	pixel->rgb.green = pixel->rgb.green * i;
	pixel->rgb.blue = pixel->rgb.blue * i;
	pixel->rgb = lightcolor(pixel->rgb, scene->a.color, i);

	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
		{
			nl = vect_scalar(n, ld);
			if (nl < 0.0)
				nl *= -1.0;
			if (nl >= 0.0)
			{
				i += light->bright * nl / (vlen(n) * vlen(ld));
				pixel->rgb = lightcolor(pixel->rgb, light->color, light->bright * nl / (vlen(n) * vlen(ld)));
			}
		}
		l = l->next;
	}
	if (i > 1.0)
		return (1.0);
	// printf("%f\n", i);
	return (i);
}

double	intersection_shadow(t_xyz o, t_xyz v, t_scene *scene)
{	
	int	i;

	i = 0;
	if (shadow_sp(o, v, scene->sp))
		return(1);
	if (shadow_pl(o, v, scene->pl))
		return(1);
	// else if (shadow_cy(o, v, scene->cy))
	// 	return(1);
	if (shadow_sq(o, v, scene->tr))
		return(1);
	square (shadow_sq(o, v, scene->sq))
	 	return(1);
	return(0);
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
		if (t > 0.001 && t < 1.0)
			return (t);
		pl_list = pl_list->next;
	}
	return (0);
}

double	shadow_tr(t_xyz o, t_xyz d, t_list *triangle)
{
	double	t;
	t_xyz ed1;
	t_xyz ed2;
	t_xyz tvec;
	t_xyz qvec;
	double det;
	double u;
	double v;
	t_triangle	*tr;
	t_list	*tr_list;
	tr_list = triangle;

	while(tr_list)
	{	
		tr = tr_list->content;
		ed1 = vect_direction(tr->p1, tr->p2);
		ed2 = vect_direction(tr->p3, tr->p2);
		det = vect_scalar(ed1, vector_prod(d, ed2));
		if (fabs(det) < 0.000001)
		{
			tr_list = tr_list->next;
			continue;
		}
		tvec = vect_direction(o, tr->p2);
		u = vect_scalar(tvec, vector_prod(d, ed2)) / det;
		if (u < 0.0 || u > 1.0)
		{
			tr_list = tr_list->next;
			continue;
		}
		qvec = vector_prod(tvec, ed1);
		v = vect_scalar(d, qvec) / det;
		if (v < 0.0 || v + u > 1.0)
		{
			tr_list = tr_list->next;
			continue;
		}
		t = vect_scalar(ed2, qvec) / det;
		if (t > 0.001 && t < 1.0)
			return (t);
		tr_list = tr_list->next;
	}
	return (0);
}

double	shadow_sq(t_xyz o, t_xyz d, t_list *square)
{
	double	halfsize;
	double t;
	double plane_d;
	t_xyz	p;
	t_xyz	v;
	t_square	*sq;
	t_list	*sq_list;
	sq_list = square;

	while(sq_list)
	{	
		sq = sq_list->content;
		halfsize = sq->sidesize / 2;
		plane_d = -vect_scalar(sq->vector, sq->center);
		if (fabs(vect_scalar(v, sq->vector)) < 0.0000001)
		{
			sq_list = sq_list->next;
			continue;
		}
		if (vect_scalar(v, sq->vector))
			t = -(vect_scalar(sq->vector, o) + plane_d) / vect_scalar(v, sq->vector);
		if (t < 0.0001 || t > INFINITY)
		{
			sq_list = sq_list->next;
			continue;
		}
		p = vect_sum(o, vect_mult(t, d));
		v = vect_direction(p, sq->center);
		if (fabs(v.x) <= halfsize && fabs(v.y) <= halfsize && fabs(v.z) <= halfsize)
			return (t);
		sq_list = sq_list->next;
	}
	return (0);