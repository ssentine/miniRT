/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:53:54 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 17:53:55 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

static void		create_bmp_file_header(t_scene *scene, int fd, t_rt *mini_rt)
{
	unsigned char	*header;
	int				size;

	header = ft_calloc(FILE_HEADER_SIZE, sizeof(unsigned char));
	if (header)
	{
		size = FILE_HEADER_SIZE + INFO_HEADER_SIZE +
(mini_rt->image.bits_per_pixel / 8 * scene->resolution.x) * scene->resolution.y;
		header[0] = (unsigned char)('B');
		header[1] = (unsigned char)('M');
		header[2] = (unsigned char)(size);
		header[3] = (unsigned char)(size >> 8);
		header[4] = (unsigned char)(size >> 16);
		header[5] = (unsigned char)(size >> 24);
		header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
		write(fd, header, FILE_HEADER_SIZE);
		free(header);
	}
}

static void		create_bmp_info_header(t_scene *scene, int fd, t_rt *mini_rt)
{
	unsigned char	*header;
	int				height;
	int				width;

	height = scene->resolution.y;
	width = scene->resolution.x;
	header = ft_calloc(INFO_HEADER_SIZE, sizeof(unsigned char));
	if (header)
	{
		header[0] = (unsigned char)(INFO_HEADER_SIZE);
		header[4] = (unsigned char)(width);
		header[5] = (unsigned char)(width >> 8);
		header[6] = (unsigned char)(width >> 16);
		header[7] = (unsigned char)(width >> 24);
		header[8] = (unsigned char)(height);
		header[9] = (unsigned char)(height >> 8);
		header[10] = (unsigned char)(height >> 16);
		header[11] = (unsigned char)(height >> 24);
		header[12] = (unsigned char)(1);
		header[14] = (unsigned char)(mini_rt->image.bits_per_pixel);
		write(fd, header, INFO_HEADER_SIZE);
		free(header);
	}
}

void			save_image(t_scene *scene, char *fn, t_rt *mini_rt, int width)
{
	int				fd;
	int				y;
	int				x;
	unsigned int	*dst;

	fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd)
	{
		create_bmp_file_header(scene, fd, mini_rt);
		create_bmp_info_header(scene, fd, mini_rt);
		width = scene->resolution.x;
		y = scene->resolution.y - 1;
		while (y >= 0)
		{
			x = -1;
			while (++x < width)
			{
				dst = (unsigned int*)(mini_rt->image.addr +
(y * mini_rt->image.line_length + x * (mini_rt->image.bits_per_pixel / 8)));
				write(fd, dst, 4);
			}
			y--;
		}
		close(fd);
	}
}
