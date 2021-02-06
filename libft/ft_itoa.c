/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:50:41 by rgordon           #+#    #+#             */
/*   Updated: 2020/11/12 21:41:08 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*createstr(int num, int size)
{
	char	*asc;

	asc = (char *)malloc(size + 1);
	if (!asc)
		return (NULL);
	if (num < 0)
	{
		asc[0] = '-';
		num /= -1;
	}
	asc[size] = '\0';
	while (num != 0)
	{
		asc[size - 1] = num % 10 + 48;
		num = num / 10;
		size--;
	}
	return (asc);
}

char		*ft_itoa(int n)
{
	int		i;
	int		temp;
	char	*result;

	i = 0;
	temp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	result = createstr(temp, i);
	return (result);
}
