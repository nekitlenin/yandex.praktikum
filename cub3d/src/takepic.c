/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takepic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:38 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:38 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void		image_data(t_config *set, int fd)
{
	unsigned char	head[40];
	int				n;

	ft_bzero(head, 40);
	head[0] = 40;
	n = set->w_resol;
	head[4] = n % 256;
	head[5] = n / 256 % 256;
	head[6] = n / 256 / 256 % 256;
	head[7] = n / 256 / 256 / 256;
	n = set->h_resol;
	head[8] = n % 256;
	head[9] = n / 256 % 256;
	head[10] = n / 256 / 256 % 256;
	head[11] = n / 256 / 256 / 256;
	head[12] = 1;
	head[14] = 32;
	write(fd, head, 40);
}

static void		file_data(t_config *set, int fd)
{
	unsigned char	head[14];
	int				n;

	ft_bzero(head, 14);
	head[0] = 66;
	head[1] = 77;
	n = set->w_resol * set->h_resol * 4 + 54;
	head[2] = n % 256;
	head[3] = n / 256 % 256;
	head[4] = n / 256 / 256 % 256;
	head[5] = n / 256 / 256 / 256;
	head[10] = 54;
	write(fd, head, 14);
}

static void		pixel_data(t_config *set, int fd)
{
	int		x;
	int		y;

	y = (set->h_resol - 1) * set->w_resol;
	while (y >= 0)
	{
		x = -1;
		while (++x < set->w_resol)
			write(fd, &set->addr[(x + y) * 4], 4);
		y -= set->w_resol;
	}
}

int				take_pic(t_config *set)
{
	int	fd;

	fd = open("screenshot.bmp", \
			O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
	file_data(set, fd);
	image_data(set, fd);
	pixel_data(set, fd);
	close(fd);
	return (0);
}
