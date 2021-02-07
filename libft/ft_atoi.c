/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:58:04 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/07 21:10:27 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	white_space(char c)
{
	if (((c >= 9) && (c <= 13)) || (c == 32) || (c == '\f'))
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int sign;
	int num;

	sign = 1;
	num = 0;
	while (white_space(*str))
		str++;
	if (*str == '+' || (*str == '-'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (!ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		str++;
	}
	return (num * sign);
}
