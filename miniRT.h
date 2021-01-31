/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:55:09 by rgordon           #+#    #+#             */
/*   Updated: 2021/01/31 20:24:41 by rgordon          ###   ########.fr       */
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

typedef struct	s_scene {
	float		x;
	float		y;
}				t_scene;

typedef struct	s_alight {
	float		ratio;
	int			R;
	int			G;
	int			B;
}				t_alight;

typedef struct	s_camera {
	float		x;
	float		y;
	float		z;
	float		xv;
	float		yx;
	float		zv;
	int			fov;
}				t_camera;

typedef struct	s_light {
	float		x;
	float		y;
	float		z;
	int			R;
	int			G;
	int			B;
}				t_light;

typedef struct	s_sphere {
	float		x;
	float		y;
	float		z;
	float		d;
	int			R;
	int			G;
	int			B;
}				t_sphere;

typedef struct	s_plane {
	float		x;
	float		y;
	float		z;
	float		xv;
	float		yx;
	float		zv;
	int			R;
	int			G;
	int			B;
}				t_plane;

typedef struct	s_square {
	float		x;
	float		y;
	float		z;
	float		xv;
	float		yx;
	float		zv;
	float		sidesize;
	int			R;
	int			G;
	int			B;
}				t_square;

typedef struct	s_cylinder {
	float		x;
	float		y;
	float		z;
	float		xv;
	float		yx;
	float		zv;
	float		d;
	float		height;
	int			R;
	int			G;
	int			B;
}				t_cylinder;

typedef struct	s_triangle {
	float		x1;
	float		y1;
	float		z1;
	float		x2;
	float		y2;
	float		z2;
	float		x3;
	float		y3;
	float		z3;
	int			R;
	int			G;
	int			B;
}				t_triangle;
#endif