/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:31:33 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/16 21:07:39 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	lighting(t_xyz o, t_xyz v, t_pixel *pixel, t_scene *scene)
{
	t_xyz	p;
	t_xyz	ld;
	t_light	*light;
	t_list	*l;

	p = vect_sum(o, vect_mult(pixel->t, v));
	l = scene->light;
	pixel->i = scene->a.bright;
	pixel->rgb = apply_intensity(pixel->rgb, pixel->i);
	pixel->rgb = add_color(pixel->rgb, scene->a.color, pixel->i);
	while (l)
	{
		light = l->content;
		ld = vect_direction(light->point, p);
		if (!intersection_shadow(p, ld, scene))
			calculate_intensity(pixel, ld, light);
		l = l->next;
	}
	if (pixel->i > 1.0)
		pixel->i = 1.0;
}

void	calculate_intensity(t_pixel *pixel, t_xyz ld, t_light *light)
{
	double nl;
	double i;

	nl = dot_product(pixel->n, ld);
	if (nl < 0.0 && pixel->id != SP)
		nl *= -1.0;
	if (nl >= 0.0)
	{
		i = light->bright * nl / (vect_len(pixel->n) * vect_len(ld));
		pixel->rgb = add_color(pixel->rgb, light->color, i);
		pixel->i += i;
	}
}

double	intersection_shadow(t_xyz o, t_xyz v, t_scene *scene)
{
	if (shadow_sp(o, v, scene->sp))
		return (1);
	if (shadow_pl(o, v, scene->pl))
		return (1);
	if (shadow_tr(o, v, scene->tr))
		return (1);
	if (shadow_sq(o, v, scene->sq))
		return (1);
	if (shadow_cy(o, v, scene->cy))
		return (1);
	return (0);
}
