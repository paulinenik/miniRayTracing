/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:48:01 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/19 22:21:39 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[i] && ft_strlen(s) > (size_t)start)
	{
		str[i] = ((char *)s)[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
