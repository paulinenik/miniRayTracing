/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvastoviewport.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:14:51 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/24 18:22:21 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_xyz	canvas_to_viewport(double x, double y, t_resolution res, t_camera *cam)
{
	double	fv;
	t_xyz	d;
	t_xyz	up;
	t_xyz	right;
	t_xyz	new_d;

	fv = tan(cam->fov * M_PI / 360) * 2;
	d.x = (x - (res.width / 2.0)) / res.width * fv;
	d.y = ((res.height / 2.0) - y) / res.height * fv;
	d.z = 1;
	if (cam->vector.x == 0.0 && cam->vector.z == 0.0)
		cam->vector.z = 0.1;
	cam->vector = normalize(cam->vector);
	right = cross_product((t_xyz){0.0, 1.0, 0.0}, cam->vector);
	up = cross_product(cam->vector, right);
	new_d.x = (right.x * d.x + right.y * d.y + right.z * d.z);
	new_d.y = (up.x * d.x + up.y * d.y + up.z * d.z);
	new_d.z = (cam->vector.x * d.x + cam->vector.y * d.y + cam->vector.z * d.z);
	return (new_d);
}

t_xyz	normalize(t_xyz vect)
{
	t_xyz res;

	res.x = vect.x / vect_len(vect);
	res.y = vect.y / vect_len(vect);
	res.z = vect.z / vect_len(vect);
	return (res);
}

double	vect_len(t_xyz v)
{
	return (sqrt(dot_product(v, v)));
}
