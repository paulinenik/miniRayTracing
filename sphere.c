/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:33:04 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/15 23:16:03 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	spherert(t_scene *scene)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		w;
	int		h;
	double x;
	double y;
	double t;
	double i;
	t_sphere *sp;
	t_camera *cam;
	t_rgb	rgb;
	int 	color;
	t_xyz	dot;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, scene->r.width, scene->r.height, "miniRT");
	img.img = mlx_new_image(mlx, scene->r.width, scene->r.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	w = scene->r.width;
	h = scene->r.height;
	cam = scene->cam->data;
	while(scene->sp)
	{
		x = 0;
		y = 0;
		sp = scene->sp->content;
		color = colortoint(0, sp->color.red, sp->color.green, sp->color.blue);
		while (y < h)
		{
			while (x < w)
			{
				dot = canvastoviewport(x, y, w, h);
				if ((t = intersection(cam->point, dot, sp)) != 0)
				{
					i = lighting(cam->point, dot, scene->light, t, sp->center) + scene->a.bright;
					rgb = lightcolor(sp->color, i);		
					color = colortoint(0, rgb.red, rgb.green, rgb.blue);
					my_mlx_pixel_put(&img, x, y, color);
				}
				// else
				// 	my_mlx_pixel_put(&img, x, y, colortoint(0, 52, 94, 235));
				x++;
			}
			y++;
			x = 0;
		}
		scene->sp = scene->sp->next;
	}
	my_mlx_pixel_put(&img, 5, 5, color);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

double	intersection(t_xyz o, t_xyz v, t_sphere *sp)
{
	t_xyz d;
	t_xyz oc;
	double	r;
	double	k1;
	double	k2;
	double	k3;
	double	discr;
	double t1;
	double t2;

	d = vect_direction(v, o);
	oc = vect_direction(o, sp->center);
	r = sp->diameter / 2;

	k1 = vect_scalar(d, d);
	k2 = 2 * vect_scalar(oc, d);
	k3 = vect_scalar(oc, oc) - r * r;
	discr = k2 * k2 - 4 * k1 * k3;
	if (discr < 0)
		return (0);
	t1 = (-k2 + sqrt(discr) / (2 * k1));
	t2 = (-k2 - sqrt(discr) / (2 * k1));
	if (t1 <= t2 && t1 > 0.0 && t1 < INFINITY)
		return (t1);
	if (t2 > 0.0 && t2 < INFINITY)
		return (t2);
	return (0);
}

double	lighting(t_xyz o, t_xyz v, t_list *l, double t, t_xyz c)
{
	t_xyz p;
	t_xyz n;
	t_xyz ld;
	double nl;
	t_light	*light;
	double i;

	i = 0.0;
	p = vect_sum(o, vect_mult(t, vect_direction(v, o)));
	n = vect_direction(p, c);
	n = vect_mult(1 / vlen(n), n);

	// while(l)
	// {
		light = l->content;
		ld = vect_direction(light->point, p);
		nl = vect_scalar(n, ld);
		if (nl > 0.0)
			i += light->bright * nl / (vlen(n) * vlen(ld));
	// 	l = l->next;
	// }
	if (i > 1.0)
		return (1.0);
	return (i);
}
