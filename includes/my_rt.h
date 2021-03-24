/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_rt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:33:57 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/24 18:50:33 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_RT_H
# define MY_RT_H

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

int				colortoint(int t, int r, int g, int b);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				close_window(t_data *data);

#endif
