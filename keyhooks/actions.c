/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:50:06 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/17 18:50:27 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_resolution(void *mlx, t_scene *scene)
{
	int		x;
	int 	y;
	double	ratio;

	ratio = scene->r.height / scene->r.width;
	mlx_get_screen_size(mlx, &x, &y);
	if(scene->r.width > x || scene->r.height > y)
	{
		if (ratio - 1 <= 0.000001)
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
	exit(0);
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
