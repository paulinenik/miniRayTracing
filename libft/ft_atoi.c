/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:58:04 by rgordon           #+#    #+#             */
/*   Updated: 2020/11/12 21:52:41 by rgordon          ###   ########.fr       */
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
	int i;
	int sign;
	int num;

	i = 0;
	sign = 1;
	num = 0;
	while (white_space(str[i]) == 1)
		i++;
	if (str[i] == '+' || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + str[i] - 48;
		i++;
		if ((!((str[i] >= '0') && (str[i] <= '9'))) || (str[i] == '\0'))
			return (num * sign);
	}
	return (0);
}
