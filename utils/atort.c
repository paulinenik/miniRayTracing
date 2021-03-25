/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:48:48 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:15:39 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <math.h>

static int	check_minus(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	return (sign);
}

int			rt_atoi(char *str, t_scene *scene)
{
	int		num;
	int		sign;
	char	*temp;

	num = 0;
	temp = str;
	sign = check_minus(&temp);
	while (ft_isdigit(*temp))
	{
		num = num * 10 + *temp - 48;
		temp++;
	}
	if (*temp)
		ft_error_rt(map_invalid, scene);
	return (num * sign);
}

double		ft_atof(char *str, t_scene *scene)
{
	int		sign;
	int		temp;
	double	num;
	int		dot;
	char	*tmp;

	dot = 0;
	temp = 0;
	num = 0;
	tmp = str;
	sign = check_minus(&tmp);
	while (ft_isdigit(*tmp))
	{
		num = num * 10 + *tmp - 48;
		tmp++;
		if (*tmp == '.')
		{
			tmp++;
			temp = ft_strlen(tmp);
		}
	}
	if (*tmp)
		ft_error_rt(map_invalid, scene);
	return (num * sign / pow(10, temp));
}

t_rgb		atorgb(char *str, t_scene *scene)
{
	t_rgb	color;
	char	**arr;

	arr = ft_split(str, ',');
	if (!arr)
		ft_error_rt(malloc_err, scene);
	color.red = rt_atoi(arr[0], scene);
	color.green = rt_atoi(arr[1], scene);
	color.blue = rt_atoi(arr[2], scene);
	if (arr[3])
		ft_error_rt(map_invalid, scene);
	if (color.red < 0 || color.red > 255)
		ft_error_rt(color_out_range, scene);
	if (color.green < 0 || color.green > 255)
		ft_error_rt(color_out_range, scene);
	if (color.blue < 0 || color.blue > 255)
		ft_error_rt(color_out_range, scene);
	split_free(arr);
	return (color);
}

t_xyz		ato_xyz(char *str, t_scene *scene)
{
	t_xyz	coo;
	char	**arr;

	arr = ft_split(str, ',');
	if (!arr)
		ft_error_rt(malloc_err, scene);
	coo.x = ft_atof(arr[0], scene);
	coo.y = ft_atof(arr[1], scene);
	coo.z = ft_atof(arr[2], scene);
	if (arr[3])
		ft_error_rt(map_invalid, scene);
	split_free(arr);
	return (coo);
}
