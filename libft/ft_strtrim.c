/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:40:25 by rgordon           #+#    #+#             */
/*   Updated: 2020/11/12 21:46:04 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		checker(char const *set, char c)
{
	int i;

	i = 0;
	while (set[i] != c && set[i])
		i++;
	if (set[i] == c)
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (checker(set, s1[start]) == 1 && (start < end))
		start++;
	if (start >= end)
		return (ft_strdup(""));
	while (checker(set, s1[end]) == 1)
		end--;
	if (!(str = (char *)malloc(end - start + 2)))
		return (NULL);
	while (start + i <= end)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
