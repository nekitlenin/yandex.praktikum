/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:32 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:32 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void		qsort_sp(t_config *set, int i0, int in)
{
	t_sp	b;
	int		l;
	int		r;

	l = i0;
	r = in;
	b = set->sps[l];
	while (l < r)
	{
		while (set->sps[r].len <= b.len && l < r)
			r--;
		if (l != r)
			set->sps[l++] = set->sps[r];
		while (set->sps[l].len >= b.len && l < r)
			l++;
		if (l != r)
			set->sps[r--] = set->sps[l];
	}
	set->sps[l] = b;
	if (i0 < l)
		qsort_sp(set, i0, l - 1);
	if (l < in)
		qsort_sp(set, l + 1, in);
}

static double	check_cross_sp(t_config *set, t_vec sp)
{
	double	res;
	double	temp;

	res = vec_mul(set->see, (vec_sum(sp, vec_rot(vec_x(vec_norm(sp), \
													0.5), R90), '+')));
	temp = vec_mul(set->see, (vec_sum(sp, vec_rot(vec_x(vec_norm(sp), \
													0.5), L90), '+')));
	if (temp > res)
		res = temp;
	return (res);
}

static void		draw_it(t_config *set, t_sp sp, t_vec scr, t_vec t)
{
	int		color;
	double	step_x;
	double	step_y;

	step_y = 1.0 * set->sp_tex.h / sp.h;
	step_x = set->w_resol > set->h_resol ? step_y : 1.0 * set->sp_tex.w / sp.w;
	while (scr.x < sp.sc_end.x && t.x < set->sp_tex.w)
	{
		scr.y = sp.scr_ypos;
		t.y = sp.tex_ypos;
		while (scr.y < sp.sc_end.y && t.y < set->sp_tex.h)
		{
			color = *(unsigned int*)(set->sp_tex.addr + \
				(int)t.y * set->sp_tex.len + (int)t.x * (set->sp_tex.bpp / 8));
			if (color != 0 && set->d_buff[(int)scr.x] > sp.dist)
				my_pixelput(set, scr.x, scr.y, color);
			scr.y++;
			t.y += step_y;
		}
		scr.x++;
		t.x += step_x;
	}
}

static void		draw_sprite(t_config *set, int x, t_sp sp)
{
	t_vec	scr;
	t_vec	t;

	sp.h = (int)(set->h_resol / sp.dist);
	sp.w = (set->w_resol > set->h_resol) ? sp.h : (int)(set->w_resol / sp.dist);
	sp.scr_ypos = (set->h_resol - sp.h) / 2;
	sp.tex_ypos = 0;
	if (sp.scr_ypos < 0)
	{
		sp.scr_ypos = 0;
		sp.tex_ypos = set->sp_tex.h * (abs(set->h_resol - sp.h) / 2) / sp.h;
	}
	sp.sc_end.y = (set->h_resol + sp.h) / 2;
	sp.sc_end.y = sp.sc_end.y >= set->h_resol ? set->h_resol - 1 : sp.sc_end.y;
	scr.x = x - sp.w / 2;
	t.x = 0;
	if (scr.x < 0)
	{
		scr.x = 0;
		t.x = set->sp_tex.w * abs(x - sp.w / 2) / sp.w;
	}
	sp.sc_end.x = x + sp.w / 2;
	if (sp.sc_end.x >= set->w_resol)
		sp.sc_end.x = set->w_resol;
	draw_it(set, sp, scr, t);
}

void			sprites(t_config *set)
{
	int		i;
	double	sp_cos;
	int		sp_dx;
	double	det;

	i = -1;
	while (++i < set->count_sp)
		set->sps[i].len = vec_len(vec_sum(set->plr, set->sps[i].crd, '-'));
	qsort_sp(set, 0, set->count_sp - 1);
	i = -1;
	while (++i < set->count_sp)
	{
		set->sps[i].sp = vec_sum(set->sps[i].crd, set->plr, '-');
		if (check_cross_sp(set, set->sps[i].sp) > 0.835)
		{
			sp_cos = vec_mul(set->see, vec_norm(set->sps[i].sp));
			set->sps[i].dist = set->sps[i].len * sp_cos;
			sp_dx = (set->w_resol / 2) * sqrt(1 / pow(sp_cos, 2) - 1) / 0.66;
			det = set->see.x * set->sps[i].sp.y - set->see.y * set->sps[i].sp.x;
			if (det <= 0)
				draw_sprite(set, set->w_resol / 2 - sp_dx, set->sps[i]);
			else
				draw_sprite(set, set->w_resol / 2 + sp_dx, set->sps[i]);
		}
	}
}
