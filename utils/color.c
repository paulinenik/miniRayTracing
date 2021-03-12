/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:48:52 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/12 21:57:22 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rgb_to_int(t_rgb color, double i)
{
	color.red *= i;
	color.green *= i;
	color.blue *= i;
	return (color.red << 16 | color.green << 8 | color.blue);
}

t_rgb	add_color(t_rgb color, t_rgb light, double i)
{
	color.red += light.red * i;
	color.green += light.green * i;
	color.blue += light.blue * i;
	if (color.blue > 255)
		color.blue = 255;
	if (color.red > 255)
		color.red = 255;
	if (color.green > 255)
		color.green = 255;
	return (color);
}

t_rgb	apply_intensity(t_rgb color, double i)
{
	color.red *= i;
	color.green *= i;
	color.blue *= i;
	return (color);
}
