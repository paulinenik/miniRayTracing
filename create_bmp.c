/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:27:55 by rgordon           #+#    #+#             */
/*   Updated: 2021/03/21 18:37:15 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
** FileType	2 bytes	A 2 character string value in ASCII to specify a DIB file type. 
					It must be 'BM' or '0x42 0x4D' in hexadecimals for modern compatibility reasons.
** FileSize	4 bytes	An integer (unsigned) representing entire file size in bytes. This value is 
					basically the number of bytes in a BMP image file.
** Reserved	2 bytes	These 2 bytes are reserved to be utilized by an image processing application 
					to add additional meaningful information. It should be initialized to '0' integer 
					(unsigned) value.
** Reserved	2 bytes	Same as the above.
** PixelDataOffset	4 bytes	An integer (unsigned) representing the offset of actual pixel data in bytes. 
					In nutshell:- it is the number of bytes between start of the file (0) and the first 
					byte of the pixel data.
*/
static void write_int_to_bmp(int index, int info, char **header)
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
	header = (char *)malloc(header_size * sizeof(char));
	size = header_size + info_size + (scene->r.width * scene->r.height);
	if (header == NULL)
		ft_error_rt(MALLOC_ERR, scene);
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
}

/*
** HeaderSize		4 bytes	An integer (unsigned) representing the size of the header in bytes. 
							It should be '40' in decimal to represent BITMAPINFOHEADER header type.
** ImageWidth		4 bytes	An integer (signed) representing the width of the final image in pixels.
** ImageHeight		4 bytes	An integer (signed) representing the height of the final image in pixels.
** Planes			2 bytes	An integer (unsigned) representing the number of color planes of the target device.
							Should be '1' in decimal.
** BitsPerPixel		2 bytes	An integer (unsigned) representing the number of bits (memory) a pixel takes 
							(in pixel data) to represent a color.
** Compression		4 bytes	An integer (unsigned) representing the value of compression to use. Should be '0' 
							in decimal to represent no-compression (identified by 'BI_RGB').
** ImageSize		4 bytes	An integer (unsigned) representing the final size of the compressed image. 
							Should be '0' in decimal when no compression algorithm is used.
** XpixelsPerMeter	4 bytes	An integer (signed) representing the horizontal resolution of the target device. 
							This parameter will be adjusted by the image processing application but should 
							be set to '0' in decimal to indicate no preference.
** YpixelsPerMeter	4 bytes	An integer (signed) representing the verical resolution of the target device 
							(same as the above).
** TotalColors		4 bytes	An integer (unsigned) representing the number of colors in the color pallet (size 
							of the color pallet or color table). If this is set to '0' in decimal :- 2^BitsPerPixel 
							colors are used.
** ImportantColors	4 bytes	An integer (unsigned) representing the number of important colors. Generally ignored 
							by setting '0' decimal value.
*/

void	generate_bmp_info(int fd, t_scene *scene)
{
	char	*header;
	int		i;

	i = 15;
	header = (char *)malloc(info_size * sizeof(char));
	if (header == NULL)
		ft_error_rt(MALLOC_ERR, scene);
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	rt_image(scene, &img);
	path = ft_strjoin(name, ".bmp");
	if (path == NULL)
		ft_error_rt(MALLOC_ERR, scene);
	free(name);
	name = NULL;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd <= 2)
		ft_error_rt(BMP_CREATE_ER, scene);
	else
	{
		generate_bmp_header(fd, scene);
		generate_bmp_info(fd, scene);
		convert_to_bmp_data(fd, scene, img);
		close(fd);
		printf("Done!\n");
	}
}