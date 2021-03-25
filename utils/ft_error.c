/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:02:43 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:22:21 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

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

	err_message[map_required] = "A map required.";
	err_message[count_arg_err] = "Too many arguments.";
	err_message[map_conf_err] = "Non-compatible extension of map file.";
	err_message[open_err] = "An error encountered while opening map file.";
	err_message[wrong_arg_err] = "Invalid option.";
	ft_putstr_fd("Error.\n", 1);
	ft_putstr_fd(err_message[errno], 1);
	ft_putstr_fd(" Please, try again.\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_error_rt(int errno, t_scene *scene)
{
	char	*err_message[15];

	err_message[read_err] = "An error encountered while reading map file.";
	err_message[malloc_err] = "Memory was not allocated.";
	err_message[map_invalid] = "Invalid map.";
	err_message[map_r_err] = "Invalid resolution values.";
	err_message[map_bright_err] = "The brightness of light is out of range.";
	err_message[color_out_range] = "Invalid color values.";
	scene_free(scene);
	ft_putstr_fd("Error.\n", 1);
	ft_putstr_fd(err_message[errno], 1);
	ft_putstr_fd(" Please, try again.\n", 1);
	exit(EXIT_FAILURE);
}
