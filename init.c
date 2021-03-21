/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:19:56 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/19 22:24:13 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_ex(char *str)
{
	str += ft_strlen(str) - 3;
	if (ft_strncmp(".rt", str, ft_strlen(str)))
		return(1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		save;
	char	*name;

	save = 0;
	name = NULL;
	if (argc == 1)
		ft_error(MAP_REQUIRED);
	if (argc > 3)
		ft_error(COUNT_ARG_ERR);
	if	(argc == 3 && ft_strncmp(argv[2], "--save", 6))
		ft_error(WRONG_ARG_ERR);
	else if (argc == 3)
	{
		save = 1;
		name = ft_substr(argv[1], 0, ft_strlen(argv[1]) - 3);
	}
	if (ft_strlen(argv[1]) < 4 || check_ex(argv[1]))
		ft_error(MAP_CONF_ERR);
	fd = open(argv[1], O_RDWR);
	if ((fd < 0))
		ft_error(OPEN_ERR);
	parse(fd, save, name);
	close(fd);
	return (0);
}