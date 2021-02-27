/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:26:41 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/27 19:39:00 by rgordon          ###   ########.fr       */
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
	rt_plane(scene, cam->point, v, &pixel);
	// rt_cylinder(scene, v, &pixel);
	// rt_square(scene, v, &pixel);
	// rt_triangle(scene, v, &pixel);
	return(pixel.color);
}
