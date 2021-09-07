/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:27 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:27 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void	choose_texture(t_config *set, t_ray ray, t_tex *txt, t_vec *t)
{
	if (ray.side == 0)
	{
		*txt = ray.dir.y < 0 ? set->no_tex : set->so_tex;
		t->x = (int)(txt->w * (ray.pos.x - (int)ray.pos.x));
		if (ray.dir.y > 0)
			t->x = txt->w - t->x - 1;
	}
	else
	{
		*txt = ray.dir.x < 0 ? set->we_tex : set->ea_tex;
		t->x = (int)(txt->w * (ray.pos.y - (int)ray.pos.y));
		if (ray.dir.x < 0)
			t->x = txt->w - t->x - 1;
	}
}

static void	floor_n_ceil(t_config *set, t_vec ends, int x)
{
	t_vec	cl;
	t_vec	fl;

	cl.x = 0;
	cl.y = ends.x;
	fl.x = ends.y;
	fl.y = set->h_resol - 1;
	draw_vline(set, x, cl, set->c_color);
	draw_vline(set, x, fl, set->f_color);
}

static void	wall(t_config *set, t_ray ray, int x, t_vec ends)
{
	t_tex	txt;
	t_vec	scr;
	t_vec	t;
	t_vec	step_n_ypos;

	choose_texture(set, ray, &txt, &t);
	scr.x = x;
	step_n_ypos.x = 1.0 * txt.h / ray.line_h;
	scr.y = ends.x;
	step_n_ypos.y = (ends.x - set->h_resol / 2 + ray.line_h / 2) \
													* step_n_ypos.x;
	while (scr.y <= ends.y)
	{
		t.y = (int)step_n_ypos.y & (txt.h - 1);
		step_n_ypos.y += step_n_ypos.x;
		my_pixelput(set, scr.x, scr.y, *(unsigned int*)(txt.addr + \
						(int)t.y * txt.len + (int)t.x * (txt.bpp / 8)));
		scr.y++;
	}
	floor_n_ceil(set, ends, x);
}

int			rendering(t_config *set)
{
	int		x;
	double	cam;
	t_ray	ray;
	t_vec	ends;

	set->plane = vec_x(vec_rot(set->see, R90), 0.66);
	x = -1;
	while (++x < set->w_resol)
	{
		cam = 2 * x / (double)set->w_resol - 1;
		ray.dir = vec_norm(vec_sum(set->see, vec_x(set->plane, cam), '+'));
		cast(set, &ray);
		set->d_buff[x] = ray.dist_w;
		ray.line_h = (int)(set->h_resol / ray.dist_w);
		ends.x = set->h_resol / 2 - ray.line_h / 2;
		ends.x = ends.x < 0 ? 0 : ends.x;
		ends.y = set->h_resol / 2 + ray.line_h / 2;
		ends.y = ends.y >= set->h_resol ? set->h_resol - 1 : ends.y;
		wall(set, ray, x, ends);
	}
	sprites(set);
	return (0);
}

int			for_loop(t_config *set)
{
	rendering(set);
	mlx_put_image_to_window(set->mlx, set->win, set->img, 0, 0);
	mlx_do_sync(set->mlx);
	return (0);
}
