/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterror.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:34:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/09 23:41:02 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTERROR_H
# define RTERROR_H

typedef enum	errors {
	MAP_REQUIRED, //argc == 1
	MAP_CONF_ERR, //not .rt file
	OPEN_ERR, //open < 0
	READ_ERR, //gnl -1
	WRONG_ARG_ERR, // argv mistake
	COUNT_ARG_ERR, //argc > 3
	MALLOC_ERR,
	MAP_INVALID, //лишние символы карты
	MAP_R_ERR, //resol out of range
	MAP_BRIGHT_ERR, //brightness out of range
	COLOR_OUT_RANGE
}				t_errors;

void	ft_error_rt(int errno, t_scene scene);
void	ft_error(int errno);

#endif