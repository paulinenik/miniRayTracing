/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvastoviewport.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:14:51 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/17 22:16:54 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

t_xyz	canvastoviewport(double x, double y, t_resolution res, int fov)
{
	t_xyz	d;
	double	fv;

	fv = tan(fov * (M_PI / 360)) * 2;
	d.x = ((float)x - (res.width / 2)) / res.width * fv;
	d.y = ((res.height / 2) - (float)y) / res.height * fv;
	d.z = 1;
	return(d);
}
t_xyz	vect_sum(t_xyz a, t_xyz b)
{
	t_xyz dot;

	dot.x = a.x + b.x;
	dot.y = a.y + b.y;
	dot.z = a.z + b.z;
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

double		vect_scalar(t_xyz a, t_xyz b)
{
	double scal = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scal);
}

t_xyz		vect_mult(double a, t_xyz dot)
{
	t_xyz res;

	res.x = dot.x * a;
	res.y = dot.y * a;
	res.z = dot.z * a;
	return (res);
}

t_xyz		vect_norm(double a, t_xyz dot)
{
	t_xyz res;

	res.x = dot.x / a;
	res.y = dot.y / a;
	res.z = dot.z / a;
	return (res);
}
double		vlen(t_xyz v)
{
	double len;

	// len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	len = sqrt(vect_scalar(v, v));
	return (len);
}

int	lightcolor(t_rgb color, double i)
{
	color.red *= i;
	color.green *= i;
	color.blue *= i;

	if (color.blue > 255)
		color.blue = 255;
	if (color.red > 255)
		color.red = 255;
	if (color.green > 255)
		color.green = 255;
	return(color.red << 16 | color.green << 8 | color.blue);
}