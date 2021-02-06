/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:13:41 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/06 18:16:17 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		ft_isspace(int c)
{
	if (c == 32)
		return (1);
	return (0);
}

int			rt_atoi(const char *str)
{
	int sign;
	int num;

	sign = 1;
	num = 0;
	while (ft_isspace(*str))
		str++;
	// if (!ft_isdigit(*str))
	// 	// map error
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		str++;
		if (!ft_isdigit(*str))
		{
			if (!ft_isspace(*str) && *str)
				printf("map error\n");
			return (num * sign);
		}
	}
	return (0);
}

void	parse_resolution(char *line, t_scene *scene)
{
	char **arr;

	arr = ft_split(line, ' ');
	// if (!arr)
	// 	printf("Malloc error");
	if (ft_strncmp(arr[0], "R", ft_strlen(arr[0])))
		printf("map error element doesn't exist\n");
	scene->r.width = rt_atoi(arr[1]);
	scene->r.height = rt_atoi(arr[2]);
	// if (arr[3])
	// 	printf("map error extra chars\n");
	printf("width is %d height is %d", scene->r.width, scene->r.height);
}

int		main(void)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof (t_scene));
	parse_resolution("Rs 19f20 1080 kd", scene);
	return (0);
}