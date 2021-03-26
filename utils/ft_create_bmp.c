/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:57:47 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/26 21:46:53 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	write_int_to_bmp(int index, int info, char **header)
{
	(*header)[index] = (char)(info);
	(*header)[index + 1] = (char)(info >> 8);
	(*header)[index + 2] = (char)(info >> 16);
	(*header)[index + 3] = (char)(info >> 24);
}

void	generate_bmp_header(int fd, t_scene *scene)
{
	char	*header;
	int		size;
	int		i;

	i = 6;
	header = (char *)malloc((int)header_size * sizeof(char));
	size = header_size + info_size + (scene->r.width * scene->r.height);
	if (header == NULL)
		ft_error_rt(malloc_err, scene);
	header[0] = (char)('B');
	header[1] = (char)('M');
	write_int_to_bmp(2, size, &header);
	write_int_to_bmp(10, header_size + info_size, &header);
	while (i < 10)
	{
		header[i] = (char)(0);
		i++;
	}
	write(fd, header, header_size);
	free(header);
	header = NULL;
}

void	generate_bmp_info(int fd, t_scene *scene)
{
	char	*header;
	int		i;

	i = 15;
	header = (char *)malloc((int)info_size * sizeof(char));
	if (header == NULL)
		ft_error_rt(malloc_err, scene);
	write_int_to_bmp(0, info_size, &header);
	write_int_to_bmp(4, scene->r.width, &header);
	write_int_to_bmp(8, scene->r.height, &header);
	header[12] = (char)(1);
	header[13] = (char)(0);
	header[14] = (char)(32);
	while (i < info_size)
	{
		header[i] = (char)(0);
		i++;
	}
	write(fd, header, info_size);
	free(header);
	header = NULL;
}

void	convert_to_bmp_data(int fd, t_scene *scene, t_img img)
{
	int len;
	int rows;

	rows = scene->r.height;
	len = scene->r.width * img.bits_per_pixel / 8;
	while (rows >= 0)
	{
		rows--;
		write(fd, (char *)(img.addr + rows * img.line_length), len);
	}
}

void	create_bmp(char *name, t_scene *scene)
{
	void	*mlx;
	t_img	img;
	int		fd;
	char	*path;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, scene->r.width, scene->r.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	rt_image(scene, &img);
	path = ft_strjoin(name, ".bmp");
	if (path == NULL)
		ft_error_rt(malloc_err, scene);
	free(name);
	name = NULL;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd <= 2)
		ft_error_rt(bmp_create_err, scene);
	generate_bmp_header(fd, scene);
	generate_bmp_info(fd, scene);
	convert_to_bmp_data(fd, scene, img);
	close(fd);
	printf("Done!\n");
	free(path);
	scene_free(scene);
}
