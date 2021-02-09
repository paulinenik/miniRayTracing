/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:55:09 by rgordon           #+#    #+#             */
/*   Updated: 2021/02/10 01:51:37 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define BUFFER_SIZE	10
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
//error_rt#include	"rterror.h"

typedef struct	s_dlist {
	void					*data;
	struct s_dlist	*prev;	
	struct s_dlist	*next;	
}				t_dlist;

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
	t_dlist			*cam;
	t_list			*light;
	t_list			*sp;
	t_list			*pl;
	t_list			*sq;
	t_list			*cy;
	t_list			*tr;
}				t_scene;

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

void		ft_error_rt(int errno, t_scene *scene);
void		ft_error(int errno);
int			rt_atoi(char **str, t_scene *scene);
t_rgb		atorgb(char *str, t_scene *scene);
double		ft_atof(char **str, t_scene *scene);
t_xyz		ato_xyz(char *str, t_scene *scene);
t_dlist		*ft_dlstnew(void *content);
void		ft_dlstadd(t_dlist **lst, t_dlist *new);
void		parse(int fd);
void		init_scene(t_scene **scene);
void		get_scene(char *line, t_scene *scene);
void		parse_resolution(char *line, t_scene *scene);
void		parse_ambient(char *line, t_scene *scene);
void		parse_cam(char *line, t_scene *scene);
void		parse_light(char *str, t_scene *scene);
void		parse_sp(char *line, t_scene *scene);
void		parse_pl(char *line, t_scene *scene);
void		parse_cy(char *line, t_scene *scene);
void		parse_sq(char *line, t_scene *scene);
void		parse_tr(char *line, t_scene *scene);

#endif