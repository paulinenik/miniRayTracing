/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:55:09 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/09 18:35:05 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minirt_H
# define minirt_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "my_rt.h"
// # include "rterror.h"
// # define malloc(x) NULL

typedef struct	s_dlist {
	struct s_camera	*data;
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
	double		r;
	double		oc;
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
	t_xyz		n;
}				t_triangle;

typedef struct	s_pixel {
	double		t;
	t_rgb		rgb;
	int			color;
}				t_pixel;

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
	t_list			*shadow_obj;
	double			light_sum;
}				t_scene;

typedef enum	e_errors {
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
void		split_free(char **arr);
void		scene_free(t_scene *scene);

int			rt_atoi(char *str, t_scene *scene);
t_rgb		atorgb(char *str, t_scene *scene);
double		ft_atof(char *str, t_scene *scene);
t_xyz		ato_xyz(char *str, t_scene *scene);

t_dlist		*ft_dlstnew(void *content);
void		ft_dlstadd(t_dlist **lst, t_dlist *new);

void		parse(int fd);
t_scene		*init_scene(void);
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
void		test(t_scene *scene);

double		vect_scalar(t_xyz a, t_xyz b);
t_xyz		vect_norm(double a, t_xyz dot);
t_xyz		vect_direction(t_xyz end, t_xyz start);
t_xyz		canvastoviewport(double x, double y, t_resolution res, t_camera *cam);
double		intersection_sp(t_xyz o, t_xyz v, t_sphere *sp);
// double		intersection_shadow(t_xyz o, t_xyz v, t_list *sphere);
t_xyz		vect_sum(t_xyz end, t_xyz start);
t_xyz		vect_mult(double a, t_xyz dot);
double		vlen(t_xyz v);
// double		lighting(t_xyz o, t_xyz v, t_list *l, double t, t_xyz c, double a, t_list *sp);
int			apply_intensity(t_rgb color, double i);
t_rgb	lightcolor(t_rgb color, t_rgb light, double i);


void		init_img(t_scene *scene);
void		rt_image(t_scene *scene, t_data *img);
int			trace_figures(t_scene *scene, t_xyz v);
void		rt_sphere(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
t_xyz		vector_prod(t_xyz a, t_xyz b);


void		rt_plane(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
double		intersection_pl(t_xyz o, t_xyz v, t_plane *pl);

double	lighting(t_xyz o, t_xyz v, t_pixel *pixel, t_xyz c, t_scene *scene);
double	intersection_shadow(t_xyz o, t_xyz v, t_scene *scene);
double	shadow_sp(t_xyz o, t_xyz v, t_list *sphere);
double	shadow_pl(t_xyz o, t_xyz v, t_list *plane);
double	shadow_tr(t_xyz o, t_xyz v, t_list *triangle);
double	lighting_pl(t_xyz o, t_xyz v, t_pixel *pixel, t_plane *pl, t_scene *scene);
double	lighting_tr(t_xyz o, t_xyz v, t_pixel *pixel, t_triangle *tr, t_scene *scene);
double	intersection_tr(t_xyz o, t_xyz d, t_triangle *tr);
void	rt_triangle(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);

#endif
