/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:37:37 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/12 21:41:17 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_xyz	vect_sum(t_xyz a, t_xyz b)
{
	t_xyz dot;

	dot.x = a.x + b.x;
	dot.y = a.y + b.y;
	dot.z = a.z + b.z;
	return (dot);
}

t_xyz	cross_product(t_xyz a, t_xyz b)
{
	t_xyz dot;

	dot.x = a.y * b.z - a.z * b.y;
	dot.y = a.z * b.x - a.x * b.z;
	dot.z = a.x * b.y - a.y * b.x;
	return (dot);
}

t_xyz	vect_direction(t_xyz end, t_xyz start)
{
	t_xyz dot;

	dot.x = end.x - start.x;
	dot.y = end.y - start.y;
	dot.z = end.z - start.z;
	return (dot);
}

double	dot_product(t_xyz a, t_xyz b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_xyz	vect_mult(double a, t_xyz dot)
{
	dot.x *= a;
	dot.y *= a;
	dot.z *= a;
	return (dot);
}
