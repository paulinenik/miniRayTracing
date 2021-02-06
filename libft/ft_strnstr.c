/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:55:34 by rgordon           #+#    #+#             */
/*   Updated: 2020/11/12 18:18:31 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	if (substr[j] == '\0')
		return ((char *)str);
	while (i < len && str[i])
	{
		index = i;
		while (str[i] == substr[j] && i < len)
		{
			i++;
			j++;
			if (substr[j] == '\0')
				return (&((char *)str)[index]);
		}
		j = 0;
		i = index + 1;
	}
	return (NULL);
}
