/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:55:09 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/25 19:30:41 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
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
# define EPSYLON 0.0000000001

/*
**	map_required 	argc == 1
**	map_conf_err 	not .rt file
**	open_err 		open < 0
**	read_err 		gnl error
**	wrong_arg_err 	argv mistake
**	count_arg_err 	argc > 3
**	malloc_err		malloc error
**	map_invalid 	extra symbols in .rt file
**	map_r_err	 	resolution out of range
**	map_bright_err 	brightness out of range
**	color_out_range	rgb value is out of range
**	bmp_create_err	error while creating a bmp
*/

typedef enum	e_errors {
	map_required,
	map_conf_err,
	open_err,
	read_err,
	wrong_arg_err,
	count_arg_err,
	malloc_err,
	map_invalid,
	map_r_err,
	map_bright_err,
	color_out_range,
	bmp_create_err
}				t_errors;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_data
{
	t_img	img;
	void	*mlx;
	void	*win;
	void	*rt;
	int		bmp;
}				t_data;

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
	double		size;
	t_rgb		color;
	t_xyz		n;
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

typedef enum	e_bmp
{
	header_size = 14,
	info_size = 40
}				t_bmp;

void			ft_error_rt(int errno, t_scene *scene);
void			ft_error(int errno);
void			split_free(char **arr);
void			scene_free(t_scene *scene);

int				rt_atoi(char *str, t_scene *scene);
t_rgb			atorgb(char *str, t_scene *scene);
double			ft_atof(char *str, t_scene *scene);
t_xyz			ato_xyz(char *str, t_scene *scene);

t_dlist			*ft_dlstnew(void *content);
void			ft_dlstadd(t_dlist **lst, t_dlist *new);
void			ft_dlist_clear(t_dlist **lst);

void			parse(int fd, int save, char *name);
t_scene			*init_scene(void);
void			get_scene(char *line, t_scene *scene);
void			parse_resolution(char *line, t_scene *scene);
void			parse_ambient(char *line, t_scene *scene);
void			parse_cam(char *line, t_scene *scene);
void			parse_light(char *str, t_scene *scene);
void			parse_sp(char *line, t_scene *scene);
void			parse_pl(char *line, t_scene *scene);
void			parse_cy(char *line, t_scene *scene);
void			parse_sq(char *line, t_scene *scene);
void			parse_tr(char *line, t_scene *scene);

double			dot_product(t_xyz a, t_xyz b);
t_xyz			cross_product(t_xyz a, t_xyz b);
t_xyz			normalize(t_xyz vect);
t_xyz			vect_direction(t_xyz end, t_xyz start);
t_xyz			vect_sum(t_xyz end, t_xyz start);
t_xyz			vect_mult(double a, t_xyz dot);
double			vect_len(t_xyz v);

int				rgb_to_int(t_rgb color, double i);
t_rgb			add_color(t_rgb color, t_rgb light, double i);
int				colortoint(int t, int r, int g, int b);

void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			init_img(t_scene *scene);
t_xyz			canvas_to_viewport(double x, double y, t_resolution res, \
t_camera *cam);
void			rt_image(t_scene *scene, t_img *img);
int				trace_figures(t_scene *scene, t_xyz v);
void			rt_sphere(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
void			rt_plane(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
void			rt_triangle(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
void			rt_square(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);
void			rt_cylinder(t_scene *scene, t_xyz o, t_xyz v, t_pixel *pixel);

double			intersection_sp(t_xyz o, t_xyz v, t_sphere *sp);
double			intersection_pl(t_xyz o, t_xyz v, t_plane *pl);
double			intersection_tr(t_xyz o, t_xyz d, t_triangle *tr);
double			intersection_sq(t_xyz o, t_xyz d, t_square *sq);
double			intersection_cy(t_xyz o, t_xyz v, t_cylinder *cy);

void			lighting(t_xyz o, t_xyz v, t_pixel *pixel, t_scene *scene);
void			calculate_intensity(t_pixel *pixel, t_xyz ld, t_light *light);
t_rgb			apply_intensity(t_rgb color, double i);
double			intersection_shadow(t_xyz o, t_xyz v, t_scene *scene);
double			shadow_sp(t_xyz o, t_xyz v, t_list *sphere);
t_xyz			get_normal_sp(t_xyz o, t_xyz v, double t, t_xyz c);
double			shadow_pl(t_xyz o, t_xyz v, t_list *plane);
double			shadow_tr(t_xyz o, t_xyz v, t_list *triangle);
double			shadow_sq(t_xyz o, t_xyz d, t_list *square);
double			shadow_cy(t_xyz o, t_xyz d, t_list *cylinder);
t_xyz			get_normal_cy(t_xyz o, t_xyz v, double t, t_cylinder *cy);

int				keyhooks(int keycode, t_data *data);
void			check_resolution(void *mlx, t_scene *scene);
int				close_window(t_data *data);
void			to_next_cam(t_data *data);
void			to_prev_cam(t_data *data);

void			create_bmp(char *name, t_scene *scene);
void			generate_bmp_header(int fd, t_scene *scene);
void			generate_bmp_info(int fd, t_scene *scene);
void			convert_to_bmp_data(int fd, t_scene *scene, t_img img);

#endif
