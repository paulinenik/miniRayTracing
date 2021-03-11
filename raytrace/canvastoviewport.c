/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvastoviewport.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:14:51 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/11 21:33:52 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

t_xyz	canvastoviewport(double x, double y, t_resolution res, t_camera *cam)
{
	double	fv;
	t_xyz	d;
	t_xyz	up;
	t_xyz	right;
	t_xyz	new_d;

	cam->vector = vect_norm(vlen(cam->vector), cam->vector);
	fv = tan(cam->fov * M_PI / 360) * 2;
	d.x = (x - (res.width / 2.0)) / res.width * fv;
	d.y = ((res.height / 2.0) - y) / res.height * fv;
	d.z = 1;
	right = vector_prod((t_xyz){0.0, 1.0, 0.0}, cam->vector);
	up = vector_prod(cam->vector, right);
	new_d.x = (right.x * d.x + right.y * d.y + right.z * d.z);
	new_d.y = (up.x * d.x + up.y * d.y + up.z * d.z);
	new_d.z = (cam->vector.x * d.x + cam->vector.y * d.y + cam->vector.z * d.z);
	return(new_d);
}

t_xyz	vect_sum(t_xyz a, t_xyz b)
{
	t_xyz dot;

	dot.x = a.x + b.x;
	dot.y = a.y + b.y;
	dot.z = a.z + b.z;
	return (dot);
}

t_xyz	vector_prod(t_xyz a, t_xyz b)
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

int	apply_intensity(t_rgb color, double i)
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

t_rgb	lightcolor(t_rgb color, t_rgb light, double i)
{
	color.red += light.red * i;
	color.green += light.green * i;
	color.blue += light.blue * i;
	if (color.blue > 255)
		color.blue = 255;
	if (color.red > 255)
		color.red = 255;
	if (color.green > 255)
		color.green = 255;
	return (color);
}

t_rgb	ambient_intensity(t_rgb color, double i)
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
	return (color);
}