/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:19:56 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/05 20:54:23 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, int argv)
{
	int		fd;
	char	map[10000];

	if (argc == 1)
		ft_printf("A map required. Please, try again.\n");
	else
	{
		fd = open(argv[1], O_RDWR);
		if ((parse(fd) == -1))
			ft_printf("An error encountered while reading. Please, try again.\n");
		close(fd);
	}
	return (0);
}