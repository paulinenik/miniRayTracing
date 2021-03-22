/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:02:43 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/22 21:11:18 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_free(t_scene *scene)
{
	ft_lstclear(&(scene->light));
	ft_lstclear(&(scene->sp));
	ft_lstclear(&(scene->pl));
	ft_lstclear(&(scene->sq));
	ft_lstclear(&(scene->cy));
	ft_lstclear(&(scene->tr));
	ft_dlist_clear(&(scene->cam));
	free(scene);
}

void	split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_error(int errno)
{
	char	*err_message[15];

	err_message[MAP_REQUIRED] = "A map required.";
	err_message[COUNT_ARG_ERR] = "Too many arguments.";
	err_message[MAP_CONF_ERR] = "Non-compatible extension of map file.";
	err_message[OPEN_ERR] = "An error encountered while opening map file.";
	err_message[WRONG_ARG_ERR] = "Invalid option.";
	ft_putstr_fd("Error.\n", 1);
	ft_putstr_fd(err_message[errno], 1);
	ft_putstr_fd(" Please, try again.\n", 1);
	exit(errno);
}

void	ft_error_rt(int errno, t_scene *scene)
{
	char	*err_message[15];

	err_message[READ_ERR] = "An error encountered while reading map file.";
	err_message[MALLOC_ERR] = "Memory was not allocated.";
	err_message[MAP_INVALID] = "Invalid map.";
	err_message[MAP_R_ERR] = "Invalid resolution values.";
	err_message[MAP_BRIGHT_ERR] = "The brightness of light is out of range.";
	err_message[COLOR_OUT_RANGE] = "Invalid color values.";
	scene_free(scene);
	ft_putstr_fd("Error.\n", 1);
	ft_putstr_fd(err_message[errno], 1);
	ft_putstr_fd(" Please, try again.\n", 1);
	exit(errno);
}
