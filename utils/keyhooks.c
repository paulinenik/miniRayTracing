/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:44 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:36:39 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int		keyhooks(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307)
		close_window(data);
	else if (keycode == 124 || keycode == 65363)
		to_next_cam(data);
	else if (keycode == 123 || keycode == 65361)
		to_prev_cam(data);
	return (1);
}

void	check_resolution(void *mlx, t_scene *scene)
{
	int		x;
	int		y;
	double	ratio;

	ratio = scene->r.height / scene->r.width;
	mlx_get_screen_size(mlx, &x, &y);
	if (scene->r.width > x || scene->r.height > y)
	{
		if (ratio - 1 <= EPSYLON)
			scene->r.width = y;
		else
			scene->r.width = x / ratio;
		scene->r.height = y;
	}
}

int		close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	scene_free(data->rt);
	printf("End of session.\nGood luck :)\n");
	exit(EXIT_SUCCESS);
	return (1);
}

void	to_next_cam(t_data *data)
{
	t_scene	*scene;
	t_img	*img;

	scene = data->rt;
	if (scene->cam->next != NULL)
	{
		ft_putstr_fd("Going to the next camera...\n", 1);
		scene->cam = scene->cam->next;
		img = &(data->img);
		mlx_clear_window(data->mlx, data->win);
		rt_image(scene, img);
		mlx_put_image_to_window(data->mlx, data->win, img->img, 0, 0);
	}
	else
		printf("There is only one camera declared in the file.\n");
}

void	to_prev_cam(t_data *data)
{
	t_scene	*scene;
	t_img	*img;

	scene = data->rt;
	if (scene->cam->prev != NULL)
	{
		ft_putstr_fd("Going to the previous camera...\n", 1);
		scene->cam = scene->cam->prev;
		img = &(data->img);
		mlx_clear_window(data->mlx, data->win);
		rt_image(scene, img);
		mlx_put_image_to_window(data->mlx, data->win, img->img, 0, 0);
	}
	else
		printf("There is only one camera declared in the file.\n");
}
