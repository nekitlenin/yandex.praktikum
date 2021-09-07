/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:03 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:03 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

void		my_pixelput(t_config *set, int x, int y, int color)
{
	char	*dst;

	dst = set->addr + (y * set->l_len + x * (set->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_cell(t_config *set, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < SCL)
	{
		j = 0;
		while (j++ < SCL)
			my_pixelput(set, x + j, y + i, color);
	}
}

void		draw_line(t_config *set, t_vec v1, t_vec v2, int color)
{
	t_vec	dv;
	t_vec	nv;
	int		i;

	dv = vec_sum(v2, v1, '-');
	nv = vec_norm(dv);
	i = 0;
	while (i++ <= vec_len(dv))
		my_pixelput(set, ceil(v1.x + i * nv.x), ceil(v1.y + i * nv.y), color);
}

void		draw_vline(t_config *set, int x, t_vec ends, int color)
{
	int	y_start;
	int	y_end;

	y_start = ends.x;
	y_end = ends.y;
	while (y_start++ < y_end)
		my_pixelput(set, x, y_start, color);
}

void		draw_2d_map(t_config *set)
{
	int	i;
	int	j;

	i = -1;
	while (set->map[++i])
	{
		j = -1;
		while (set->map[i][++j])
		{
			if (set->map[i][j] == '1')
				draw_cell(set, SCL * j, SCL * i, 0x01a1b2);
			if (set->map[i][j] == '2')
				draw_cell(set, SCL * j, SCL * i, 0xFFFFFF);
		}
	}
}
