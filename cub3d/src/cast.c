/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:10:50 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:10:50 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void	rayinit(t_ray *ray, t_vec *delta)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		delta->x = (double)ray->map_x - ray->pos.x;
	}
	else
	{
		ray->step.x = 1;
		delta->x = (double)ray->map_x + 1 - ray->pos.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		delta->y = (double)ray->map_y - ray->pos.y;
	}
	else
	{
		ray->step.y = 1;
		delta->y = (double)ray->map_y + 1 - ray->pos.y;
	}
}

static void	raypass(t_ray *ray, t_vec rx, t_vec ry)
{
	rx.x = rx.y * ray->dir.x / ray->dir.y;
	ry.y = ry.x * ray->dir.y / ray->dir.x;
	if (vec_len(rx) < vec_len(ry))
	{
		ray->pos = vec_sum(ray->pos, rx, '+');
		ray->side = 0;
		ray->map_y += ray->step.y;
	}
	else
	{
		ray->pos = vec_sum(ray->pos, ry, '+');
		ray->side = 1;
		ray->map_x += ray->step.x;
	}
}

void		cast(t_config *set, t_ray *ray)
{
	t_vec	delta;
	t_vec	rx;
	t_vec	ry;

	ray->map_x = (int)(set->plr.x);
	ray->map_y = (int)(set->plr.y);
	ray->pos = set->plr;
	while (set->map[ray->map_y][ray->map_x] != '1')
	{
		rayinit(ray, &delta);
		rx.y = delta.y;
		ry.x = delta.x;
		raypass(ray, rx, ry);
	}
	ray->dist_w = vec_mul(set->see, ray->dir) * \
							vec_len(vec_sum(ray->pos, set->plr, '-'));
}
