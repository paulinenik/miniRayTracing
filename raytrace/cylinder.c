/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:55:26 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/15 20:37:27 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_cylinder(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
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
			// pixel->n = get_normal_sp(o, v, t, cy->point);
			pixel->id = CY;
			// lighting(o, v, pixel, scene);
		}
		cy_list = cy_list->next;
	}
	pixel->color = rgb_to_int(pixel->rgb, pixel->i);
}

double	intersection_cy(t_xyz o, t_xyz v, t_cylinder *cy)
{
	t_eq	eq;
	t_xyz	c;

	c = vect_
	cy->oc = vect_direction(o, cy->point);
	eq.a = dot_product(v, v) - pow(dot_product(v, cy->vector), 2);
	eq.b = 2.0 * dot_product(cy->oc, v) - dot_product(v, cy->vector) * dot_product(cy->oc, cy->vector);
	eq.c = dot_product(cy->oc, cy->oc) - pow(dot_product(cy->oc, cy->vector), 2) - pow(cy->r, 2);
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