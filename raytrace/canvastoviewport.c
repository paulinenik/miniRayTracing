/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvastoviewport.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:14:51 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/15 23:19:59 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		colortoint(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

t_xyz	canvastoviewport(double x, double y, int w, int h)
{
	t_xyz	d;

	d.x = (x - (w / 2)) / w;
	d.y = ((h / 2) - y) / h;
	d.z = 0.5;
	return(d);
}
t_xyz	vect_sum(t_xyz end, t_xyz start)
{
	t_xyz dot;

	dot.x = end.x + start.x;
	dot.y = end.y + start.y;
	dot.z = end.z + start.z;
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

double		vlen(t_xyz v)
{
	double len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}

t_rgb	lightcolor(t_rgb color, double i)
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
	return(color);
}