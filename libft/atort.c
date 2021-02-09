/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:48:48 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 02:19:59 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		ft_isspace(int c)
{
	if (c == 32)
		return (1);
	return (0);
}

int			rt_atoi(char **str, t_scene *scene)
{
	int num;
	int sign;

	num = 0;
	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	if (!ft_isdigit(**str))
		ft_error_rt(MAP_INVALID, scene);
 	while (ft_isdigit(**str))
	{
		num = num * 10 + **str - 48;
		(*str)++;
	}
	if (**str)
	{
		if (!ft_isspace(**str))
			ft_error_rt(MAP_INVALID, scene);
	}
	//	printf("hello |%c|\n", **str);
	return (num * sign);
}

double			ft_atof(char **str, t_scene *scene)
{
	int sign;
	int temp;
	double num;
	int dot;

	dot = 0;
	sign = 1;
	temp = 0;
	num = 0;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		num = num * 10 + **str - 48;
		(*str)++;
		if (**str == '.')
		{
			dot = 1;
			(*str)++;
		}
		if (dot)
			temp++;
		if (!ft_isdigit(**str))
			if (!ft_isspace(**str) && **str)
				ft_error_rt(MAP_INVALID, scene);
	}
	while (temp > 1)
	{
		num /= 10;
		temp--;
	}
	return (num * sign);
}

t_rgb	atorgb(char *str, t_scene *scene)
{
	t_rgb	color;
	char	**arr;

	arr = ft_split(str, ',');
	if (!arr)
		ft_error_rt(MALLOC_ERR, scene);
	color.red = rt_atoi(&arr[0], scene);
	color.green = rt_atoi(&arr[1], scene);
	color.blue = rt_atoi(&arr[2], scene);
	if (arr[3])
		ft_error_rt(MAP_INVALID, scene);
	if (color.red < 0 || color.red > 255)
		ft_error_rt(COLOR_OUT_RANGE, scene);
	if (color.green < 0 || color.green > 255)
		ft_error_rt(COLOR_OUT_RANGE, scene);
	if (color.blue < 0 || color.blue > 255)
		ft_error_rt(COLOR_OUT_RANGE, scene);
	//free arr
	return (color);
}

t_xyz	ato_xyz(char *str, t_scene *scene)
{
	t_xyz	coo;
	char	**arr;

	arr = ft_split(str, ',');
	if (!arr)
		ft_error_rt(MALLOC_ERR, scene);
	coo.x = ft_atof(&arr[0], scene);
	coo.y = ft_atof(&arr[1], scene);
	coo.z = ft_atof(&arr[2], scene);
	if (arr[4])
		ft_error_rt(MAP_INVALID, scene);
	//free arr
	return(coo);
}
