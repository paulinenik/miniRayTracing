/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterror.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:34:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/24 18:51:01 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTERROR_H
# define RTERROR_H

/*
**	MAP_REQUIRED 	argc == 1
**	MAP_CONF_ERR 	not .rt file
**	OPEN_ERR 		open < 0
**	READ_ERR 		gnl error
**	WRONG_ARG_ERR 	argv mistake
**	COUNT_ARG_ERR 	argc > 3
**	MALLOC_ERR		malloc error
**	MAP_INVALID 	extra symbols in .rt file
**	MAP_BRIGHT_ERR 	brightness out of range
**	COLOR_OUT_RANGE	rgb value is out of range
*/

typedef enum	e_errors {
	MAP_REQUIRED,
	MAP_CONF_ERR,
	OPEN_ERR,
	READ_ERR,
	WRONG_ARG_ERR,
	COUNT_ARG_ERR,
	MALLOC_ERR,
	MAP_INVALID,
	MAP_BRIGHT_ERR,
	COLOR_OUT_RANGE
}				t_errors;

void	ft_error_rt(int errno, t_scene *scene);
void	ft_error(int errno);

#endif
