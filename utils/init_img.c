/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:26:41 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/24 17:55:00 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_img(t_scene *scene)
{
	t_data	data;
	t_img	*img;

	img = &(data.img);
	data.mlx = mlx_init();
	check_resolution(data.mlx, scene);
	data.win = mlx_new_window(data.mlx, scene->r.width, scene->r.height, \
	"miniRT");
	data.rt = scene;
	img->img = mlx_new_image(data.mlx, scene->r.width, scene->r.height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	mlx_key_hook(data.win, keyhooks, &data);
	mlx_hook(data.win, 17, 0L, close_window, &data);
	rt_image(scene, img);
	mlx_put_image_to_window(data.mlx, data.win, img->img, 0, 0);
	mlx_loop(data.mlx);
}

void	rt_image(t_scene *scene, t_img *img)
{
	double		x;
	double		y;
	t_camera	*cam;
	int			color;
	t_xyz		viewport;

	cam = scene->cam->data;
	x = 0;
	y = 0;
	while (y < scene->r.height)
	{
		while (x < scene->r.width)
		{
			viewport = canvas_to_viewport(x, y, scene->r, cam);
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
	rt_plane(scene, cam->point, v, &pixel);
	rt_triangle(scene, cam->point, v, &pixel);
	rt_cylinder(scene, cam->point, v, &pixel);
	rt_square(scene, cam->point, v, &pixel);
	return (pixel.color);
}
