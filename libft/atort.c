/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:48:48 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 16:32:05 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		ft_isspace(int c)
{
	if (c == 32)
		return (1);
	return (0);
}

int			rt_atoi(char **str)
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
	// if (!ft_isdigit(**str))
	// 	// map error
	while (ft_isdigit(**str))
	{
		num = num * 10 + **str - 48;
		(*str)++;
		if (!ft_isdigit(**str))
			if (!ft_isspace(**str) && **str)
				printf("map error\n");
	}
	return (num * sign);
}

double			ft_atof(char **str)
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
				printf("map error\n");
	}
	while (temp > 1)
	{
		num /= 10;
		temp--;
	}
	return (num * sign);
}

t_rgb	atorgb(char *str)
{
	t_rgb	color;

	color.red = rt_atoi(&str);
	if(*str == ',')
		str++;
	else
		printf("map error\n");
	color.green = rt_atoi(&str);
	printf("%s\n", str);
	if(*str == ',')
		str++;
	else
		printf("map error\n");
	color.blue = rt_atoi(&str);
	if (color.red < 0 || color.red > 255)
		printf("map error color corrupted\n");
	if (color.green < 0 || color.green > 255)
		printf("map error color corrupted\n");
	if (color.blue < 0 || color.blue > 255)
		printf("map error color corrupted\n");
	return (color);
}

t_xyz	ato_xyz(char *str)
{
	t_xyz	coo;

	coo.x = ft_atof(&str);
	if(*str == ',')
		str++;
	else
		printf("map error\n");
	coo.y = ft_atof(&str);
	if(*str == ',')
		str++;
	else
		printf("map error\n");
	coo.z = ft_atof(&str);
	return(coo);
}
