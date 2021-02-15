/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 20:37:04 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/12 23:14:29 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void test(t_scene *scene)
	{
		t_light *l;
		t_sphere *sp;
		t_plane *pl;
		t_square *sq;
		t_cylinder * cy;
		t_triangle *tr;
		void	*mlx;
		void	*mlx_win;
		t_data	img;
		// int     offset;
		int		x;
		int 	y;

		printf("\n---RESOLUTION---\n");
		printf("width is %d height is %d\n", scene->r.width, scene->r.height);
		printf("\n---AMBIENT---\n");
		printf("brigthness is %f\n", scene->a.bright);
		printf("red %d green %d blue %d\n", scene->a.color.red, scene->a.color.green, scene->a.color.blue);
		printf("\n---CAMERA---\n");
		printf("point x %f y %f z %f\n", scene->cam->data->point.x, scene->cam->data->point.y, scene->cam->data->point.z);
		printf("vector x %f y %f z %f\n", scene->cam->data->vector.x, scene->cam->data->vector.y, scene->cam->data->vector.z);
		printf("fov %d\n", scene->cam->data->fov);
		printf("\n---CAMERA 2---\n");
		scene->cam = scene->cam->next;
		printf("point x %f y %f z %f\n", scene->cam->data->point.x, scene->cam->data->point.y, scene->cam->data->point.z);
		printf("vector x %f y %f z %f\n", scene->cam->data->vector.x, scene->cam->data->vector.y, scene->cam->data->vector.z);
		printf("fov %d\n", scene->cam->data->fov);
		printf("\n---LIGHT POINT---\n");
		l = (t_light *)scene->light->content;
		printf("point x %f y %f z %f\n", l->point.x, l->point.y, l->point.z);
		printf("brightness is %f\n", l->bright);
		printf("red %d green %d blue %d\n", l->color.red, l->color.green, l->color.blue);
		printf("\n---SPHERE---\n");
		sp = (t_sphere *)scene->sp->content;
		printf("point x %f y %f z %f\n", sp->center.x, sp->center.y, sp->center.z);
		printf("diameter is %f\n", sp->diameter);
		printf("red %d green %d blue %d\n", sp->color.red, sp->color.green, sp->color.blue);
		printf("\n---SPHERE 2---\n");
		sp = (t_sphere *)scene->sp->next->content;
		printf("point x %f y %f z %f\n", sp->center.x, sp->center.y, sp->center.z);
		printf("diameter is %f\n", sp->diameter);
		printf("red %d green %d blue %d\n", sp->color.red, sp->color.green, sp->color.blue);
		printf("\n---PLANE---\n");
		pl = (t_plane *)scene->pl->content;
		printf("point x %f y %f z %f\n", pl->point.x, pl->point.y, pl->point.z);
		printf("vector x %f y %f z %f\n", pl->vector.x, pl->vector.y, pl->vector.z);
		printf("red %d green %d blue %d\n", pl->color.red, pl->color.green, pl->color.blue);
		printf("\n---SQUARE---\n");
		sq = (t_square *)scene->sq->content;
		printf("point x %f y %f z %f\n", sq->center.x, sq->center.y, sq->center.z);
		printf("vector x %f y %f z %f\n", sq->vector.x, sq->vector.y, sq->vector.z);
		printf("sidesize %f\n", sq->sidesize);
		printf("red %d green %d blue %d\n", sq->color.red, sq->color.green, sq->color.blue);
		printf("\n---CYLINDER---\n");
		cy = (t_cylinder *)scene->cy->content;
		printf("point x %f y %f z %f\n", cy->point.x, cy->point.y, cy->point.z);
		printf("vector x %f y %f z %f\n", cy->vector.x, cy->vector.y, cy->vector.z);
		printf("diameter is %f height is %f\n", cy->diameter, cy->height);
		printf("red %d green %d blue %d\n", cy->color.red, cy->color.green, cy->color.blue);
		printf("\n---TRIANGLE--\n");
		tr = (t_triangle *)scene->tr->content;
		printf("point x %f y %f z %f\n", tr->p1.x, tr->p1.y, tr->p1.z);
		printf("point x %f y %f z %f\n", tr->p2.x, tr->p2.y, tr->p2.z);
		printf("point x %f y %f z %f\n", tr->p3.x, tr->p3.y, tr->p3.z);
		printf("red %d green %d blue %d\n", tr->color.red, tr->color.green, tr->color.blue);
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, scene->r.width, scene->r.height, "miniRT");
		img.img = mlx_new_image(mlx, scene->r.width, scene->r.height);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		x = 5;
		y = 5;
		// offset = (y * img.line_length + x * (img.bits_per_pixel / 8));
		while (y < 65)
		{
			while (x < 65)
			{
				my_mlx_pixel_put(&img, x, y, create_trgb(0, cy->color.red, cy->color.green, cy->color.blue));
				x++;
			}
			y++;
			x = 5;
		}
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
	}
