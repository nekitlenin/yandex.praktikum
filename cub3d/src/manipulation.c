/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:14 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:14 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

double	vec_mul(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

void	forback(t_config *set, int keycode)
{
	t_vec	stp;

	if (keycode == 13)
	{
		stp = vec_sum(set->plr, vec_x(set->see, 0.25), '+');
		if (set->map[(int)(stp.y)][(int)(stp.x)] != '1')
			set->plr = vec_sum(set->plr, vec_x(set->see, 0.1), '+');
	}
	if (keycode == 1)
	{
		stp = vec_sum(set->plr, vec_x(set->see, 0.25), '-');
		if (set->map[(int)(stp.y)][(int)(stp.x)] != '1')
			set->plr = vec_sum(set->plr, vec_x(set->see, 0.1), '-');
	}
}

void	leftright(t_config *set, int keycode)
{
	t_vec	stp;

	if (keycode == 0)
	{
		stp = vec_sum(set->plr, vec_rot(vec_x(set->see, 0.25), L90), '+');
		if (set->map[(int)(stp.y)][(int)(stp.x)] != '1')
			set->plr = vec_sum(set->plr, vec_rot(vec_x(set->see, 0.1), \
																L90), '+');
	}
	if (keycode == 2)
	{
		stp = vec_sum(set->plr, vec_rot(vec_x(set->see, 0.25), R90), '+');
		if (set->map[(int)(stp.y)][(int)(stp.x)] != '1')
			set->plr = vec_sum(set->plr, vec_rot(vec_x(set->see, 0.1), \
																R90), '+');
	}
}

int		key_hook(int keycode, t_config *set)
{
	if (keycode == 13 || keycode == 1)
		forback(set, keycode);
	if (keycode == 0 || keycode == 2)
		leftright(set, keycode);
	if (keycode == 123)
		set->see = vec_rot(set->see, L90 / 30);
	if (keycode == 124)
		set->see = vec_rot(set->see, R90 / 30);
	if (keycode == 53)
		exxxit(set, 0, "");
	return (0);
}
