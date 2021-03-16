/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:55:09 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/17 01:22:49 by rgordon          ###   ########.fr       */
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
	double		r;
	t_xyz		oc;
	t_rgb		color;
}				t_sphere;

typedef struct	s_plane {
	t_xyz		point;
	t_xyz		vector;
	t_rgb		color;
}				t_plane;

typedef struct	s_square {
	t_xyz		center;
	t_xyz		vect;
	double		sidesize;
	t_rgb		color;
}				t_square;

typedef struct	s_cylinder {
	t_xyz		point;
	t_xyz		vector;
	double		r;
	double		height;
	t_rgb		color;
	t_xyz		oc;
	t_xyz		c;
}				t_cylinder;

typedef struct	s_triangle {
	t_xyz		a;
	t_xyz		b;
	t_xyz		c;
	t_xyz		ab;
	t_xyz		bc;
	t_rgb		color;
	t_xyz		n;
}				t_triangle;

typedef struct	s_pixel {
	double		t;
	t_rgb		rgb;
	int			color;
	t_xyz		n;
	int			id;
	double		i;
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

typedef struct	s_eq {
	double	a;
	double	b;
	double	c;
	double	discr;
	double	x1;
	double	x2;
}				t_eq;

typedef struct	s_barycentric {
	t_xyz	tvec;
	t_xyz	qvec;
	double	det;
	double	u;
	double	v;
}				t_barycentric;


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

typedef enum	e_id {
	SP,
	PL,
	SQ,
	TR,
	CY
}				t_id;

typedef	enum
{
	a = 0,
	s = 1,
	d = 2,
	f = 3,
	h = 4,
	g = 5,
	z = 6,
	x = 7,
	c = 8,
	v = 9,
	w = 13,
	plus = 24,
	minus = 27,
	arrow_left = 123,
	arrow_right = 124,
}	t_key;

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

double		dot_product(t_xyz a, t_xyz b);
t_xyz		normalize(t_xyz vect);
t_xyz		vect_direction(t_xyz end, t_xyz start);
t_xyz		canvas_to_viewport(double x, double y, t_resolution res, t_camera *cam);
double		intersection_sp(t_xyz o, t_xyz v, t_sphere *sp);
t_xyz		vect_sum(t_xyz end, t_xyz start);
t_xyz		vect_mult(double a, t_xyz dot);
double		vect_len(t_xyz v);
int			rgb_to_int(t_rgb color, double i);
t_rgb	add_color(t_rgb color, t_rgb light, double i);


void		init_img(t_scene *scene);
void		rt_image(t_scene *scene, t_img *img);
int			trace_figures(t_scene *scene, t_xyz v);
void		rt_sphere(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
t_xyz		cross_product(t_xyz a, t_xyz b);


void		rt_plane(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
double		intersection_pl(t_xyz o, t_xyz v, t_plane *pl);

void	lighting(t_xyz o, t_xyz v, t_pixel *pixel, t_scene *scene);
double	intersection_shadow(t_xyz o, t_xyz v, t_scene *scene);
double	shadow_sp(t_xyz o, t_xyz v, t_list *sphere);
double	shadow_pl(t_xyz o, t_xyz v, t_list *plane);
double	shadow_tr(t_xyz o, t_xyz v, t_list *triangle);
double	intersection_tr(t_xyz o, t_xyz d, t_triangle *tr);
void	rt_triangle(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
void	rt_square(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
double	intersection_sq(t_xyz o, t_xyz d, t_square *sq);
double	shadow_sq(t_xyz o, t_xyz d, t_list *square);


t_rgb	apply_intensity(t_rgb color, double i);
t_xyz	get_normal_sp(t_xyz o, t_xyz v, double t, t_xyz c);
void	calculate_intensity(t_pixel *pixel, t_xyz ld, t_light *light);

void	rt_cylinder(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
double	intersection_cy(t_xyz o, t_xyz v, t_cylinder *cy);
t_xyz	get_normal_cy(t_xyz o, t_xyz v, double t, t_cylinder *cy);
double	shadow_cy(t_xyz o, t_xyz d, t_list *cylinder);
int		keyhooks(int keycode, t_data *data);
void	to_next_cam(t_data *data);
void	to_prev_cam(t_data *data);
void	check_resolution(void *mlx, t_scene *scene);
#endif
