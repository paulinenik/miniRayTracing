/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:26:41 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/23 17:32:53 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_img(t_scene *scene)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, scene->r.width, scene->r.height, "miniRT");
	img.img = mlx_new_image(mlx, scene->r.width, scene->r.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	rt_image(scene, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

void	rt_image(t_scene *scene, t_data *img)
{
	double x;
	double y;
	t_camera *cam;
	int 	color;
	t_xyz	viewport;

	cam = scene->cam->data;
	x = 0;
	y = 0;
	while (y < scene->r.height)
	{
		while (x < scene->r.width)
		{
			viewport = canvastoviewport(x, y, scene->r, cam);
			color = trace_figures(scene, viewport);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
		x = 0;
	}
}

int		trace_figures(t_scene *scene, t_xyz v)
{
	t_pixel		pixel;
	t_camera	*cam;
	
	cam = (t_camera *)scene->cam->data;
	pixel.t = INFINITY;
	pixel.rgb.red = 0;
	pixel.rgb.green = 0;
	pixel.rgb.blue = 0;
	rt_sphere(scene, cam->point, v, &pixel);
	// rt_plane(scene, v, &pixel);
	// rt_cylinder(scene, v, &pixel);
	// rt_square(scene, v, &pixel);
	// rt_triangle(scene, v, &pixel);
	return(pixel.color);
}

void	rt_sphere(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel)
{
	double		i;
	double		t;
	t_sphere	*sp;
	t_list		*sp_list;

	sp_list = scene->sp;
	i = 1.0;
	while(sp_list)
	{
		sp = sp_list->content;
		if (!sp->r)
			sp->r = pow(sp->diameter / 2, 2);
		if ((t = intersection(o, v, sp)) > 0.0 && t < pixel->t)
		{
			pixel->t = t;
			pixel->rgb = sp->color;
			i = lighting(o, v, scene->light, pixel->t, sp->center, scene->a.bright, scene->sp);
		}
		sp_list = sp_list->next;
	}
	pixel->color = lightcolor(pixel->rgb, i);	
}

double	intersection(t_xyz o, t_xyz v, t_sphere *sp)
{
	t_xyz oc;
	double	k1;
	double	k2;
	double	k3;
	double	discr;
	double t1;
	double t2;

	oc = vect_direction(o, sp->center);
	k1 = vect_scalar(v, v);
	k2 = 2.0 * vect_scalar(oc, v);
	k3 = vect_scalar(oc, oc) - sp->r;
	discr = k2 * k2 - 4.0 * k1 * k3;
	if (discr < 0)
		return (0);
	t1 = (-k2 + sqrt(discr)) / (2.0 * k1);
	t2 = (-k2 - sqrt(discr)) / (2.0 * k1);
	if (t1 <= t2 && t1 > 0.0 && t1 < INFINITY)
		return (t1);
	if (t2 > 0.0 && t2 < INFINITY)
		return (t2);
	return (0);
}

double	intersection_shadow(t_xyz o, t_xyz v, t_list *sphere)
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

double	lighting(t_xyz o, t_xyz v, t_list *l, double t, t_xyz c, double a, t_list *sp)
{
	t_xyz p;
	t_xyz n;
	t_xyz ld;
	double nl;
	t_light	*light;
	double i;

	i = a;
	v = vect_mult(t, v);
	p = vect_sum(o, v);
	n = vect_direction(p, c);
	n = vect_norm(vlen(n), n);

	light = l->content;
	ld = vect_direction(light->point, p);
	if (!intersection_shadow(p, ld, sp))
	{
		nl = vect_scalar(n, ld);
		if (nl > 0.0)
			i += light->bright * nl / (vlen(n) * vlen(ld));
		if (i > 1.0)
			return (1.0);
	}
	return (i);
}
