/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:02:43 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 02:00:26 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error(int errno)
{
	char	*err_message[15];

	err_message[MAP_REQUIRED] = "A map required.";
	err_message[COUNT_ARG_ERR] = "Too many arguments.";
	err_message[MAP_CONF_ERR] = "Non-compatible extension of map file.";
	err_message[OPEN_ERR] = "An error encountered while opening map file.";
	err_message[WRONG_ARG_ERR] = "Invalid option. Try '--help' for more information.";
	ft_putstr_fd("Error.\n", 1);
	ft_putstr_fd(err_message[errno], 1);
}

void	ft_error_rt(int errno, t_scene *scene)
{
	//clear scene;
	char	*err_message[15];

	err_message[READ_ERR] = "An error encountered while reading map file.";
	err_message[MALLOC_ERR] = "Memory was not allocated.";
	err_message[MAP_INVALID] = "Invalid map.";
	err_message[MAP_R_ERR] = "Invalid resolution values.";
	err_message[MAP_BRIGHT_ERR] = "The brightness ratio of lightning is out of range.";
	err_message[COLOR_OUT_RANGE] = "Invalid color values.";

	scene->r.height = 0;
	ft_putstr_fd("Error.\n", 1);
	ft_putstr_fd(err_message[errno], 1);
	//exit(errno);
}