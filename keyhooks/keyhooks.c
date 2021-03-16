/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:44 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/16 23:28:02 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	scene_free(data->rt);
	exit(0);
	return (1);
}