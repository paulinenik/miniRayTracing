/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:55:09 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/08 17:12:00 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include	<stdlib.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/uio.h>
#include	<stdio.h>
#include	<string.h>
#include	<math.h>
//#include	<mlx.h>
#include	"libft.h"
#include	"get_next_line.h"

typedef struct	s_double_list {
	void					*data;
	struct s_double_list	*prev;	
	struct s_double_list	*next;	
}				t_double_list;

typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;

typedef struct	s_rgb {
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct	s_resolution {
	int			width;
	int			height;
}				t_resolution;

typedef struct	s_ambient {
	double		bright;
	t_rgb		color;
}				t_ambient;

typedef struct	s_camera {
	t_xyz		point;
	t_xyz		vector;
	int			fov;
}				t_camera;

typedef struct	s_light {
	t_xyz		point;
	double		bright;
	t_rgb		color;
}				t_light;

typedef struct	s_sphere {
	t_xyz		center;
	double		diameter;
	t_rgb		color;
}				t_sphere;

typedef struct	s_plane {
	t_xyz		point;
	t_xyz		vector;
	t_rgb		color;
}				t_plane;

typedef struct	s_square {
	t_xyz		center;
	t_xyz		vector;
	double		sidesize;
	t_rgb		color;
}				t_square;

typedef struct	s_cylinder {
	t_xyz		point;
	t_xyz		vector;
	double		diameter;
	double		height;
	t_rgb		color;
}				t_cylinder;

typedef struct	s_triangle {
	t_xyz		p1;
	t_xyz		p2;
	t_xyz		p3;
	t_rgb		color;
}				t_triangle;

typedef struct	s_scene {
	t_resolution	r;
	t_ambient		a;
	t_double_list	*cam;
	t_list			*light;
	t_list			*sp;
	t_list			*pl;
	t_list			*sq;
	t_list			*cy;
	t_list			*tr;
}				t_scene;

int			rt_atoi(char **str);
t_rgb	atorgb(char *str);
double			ft_atof(char **str);
t_xyz	ato_xyz(char *str);

#endif