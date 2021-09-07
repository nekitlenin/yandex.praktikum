/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:44 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:44 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

t_vec	vec_x(t_vec v, double n)
{
	t_vec	vr;

	vr.x = v.x * n;
	vr.y = v.y * n;
	return (vr);
}

t_vec	vec_sum(t_vec v1, t_vec v2, char act)
{
	t_vec	vr;

	if (act == '+')
	{
		vr.x = v1.x + v2.x;
		vr.y = v1.y + v2.y;
	}
	if (act == '-')
	{
		vr.x = v1.x - v2.x;
		vr.y = v1.y - v2.y;
	}
	return (vr);
}

double	vec_len(t_vec v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2)));
}

t_vec	vec_norm(t_vec v)
{
	t_vec	vr;

	vr.x = v.x / vec_len(v);
	vr.y = v.y / vec_len(v);
	return (vr);
}

t_vec	vec_rot(t_vec v, double ang)
{
	t_vec	vr;

	vr.x = v.x * cos(ang) - v.y * sin(ang);
	vr.y = v.x * sin(ang) + v.y * cos(ang);
	return (vr);
}
