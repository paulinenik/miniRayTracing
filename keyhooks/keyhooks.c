/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:44 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/17 00:46:56 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		keyhooks(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307)
		close_window(data);
	else if (keycode == arrow_right || keycode == 65363)
		to_next_cam(data);
	else if (keycode == arrow_left || keycode == 65361)
		to_prev_cam(data);
	return (1);
}