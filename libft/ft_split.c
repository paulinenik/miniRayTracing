/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 21:05:44 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 20:08:50 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	if (s[i] != c)
		word = 1;
	else
		word = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			word++;
		i++;
	}
	return (word);
}

static void	freeall(char **arr, int words)
{
	int	i;

	i = 0;
	while (words != 0)
	{
		free(arr[words - 1]);
		i--;
	}
	free(arr);
}

static char	**ft_arrwrite(char **arr, char *s1, char c, int n)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	while (i < n)
	{
		if ((s2 = ft_strchr(s1, c)) == NULL)
			s2 = s1 + ft_strlen(s1);
		if ((arr[i] = (char *)malloc(s2 - s1 + 1)) == NULL)
		{
			freeall(arr, n);
			return (NULL);
		}
		j = -1;
		while (++j < s2 - s1 && s1[j])
			arr[i][j] = s1[j];
		arr[i][j] = '\0';
		while (*s2 == c && s2)
			s2++;
		s1 = s2;
		i++;
	}
	return (arr);
}

char		**ft_split(char const *s, char c)
{
	char	**arr;
	char	*s1;
	int		word;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0)
		word = 0;
	else
		word = words_count((char *)s, c);
	s1 = (char *)s;
	arr = (char **)malloc(sizeof(char *) * (word + 1));
	if (!arr)
		return (NULL);
	while (*s1 == c)
		s1++;
	arr = ft_arrwrite(arr, s1, c, word);
	arr[word] = NULL;
	return (arr);
}
