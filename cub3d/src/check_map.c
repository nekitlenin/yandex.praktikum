/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:10:59 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:10:59 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void	get_sprites(t_config *set)
{
	int		i;
	int		j;
	int		n;

	n = set->count_sp;
	set->sps = (t_sp *)malloc(sizeof(t_sp) * set->count_sp);
	i = -1;
	while (set->map[++i])
	{
		j = -1;
		while ((set->map)[i][++j])
		{
			if (set->map[i][j] == '2' && --n >= 0)
			{
				set->sps[n].crd.x = j + 0.5;
				set->sps[n].crd.y = i + 0.5;
			}
		}
	}
}

static void	get_pos(t_config *set, int x, int y, char ch)
{
	if (set->plr.x < 0 && set->plr.y < 0)
	{
		set->plr.x = x + 0.5;
		set->plr.y = y + 0.5;
		if (ch == 'S')
			set->see.y = 1;
		if (ch == 'N')
			set->see.y = -1;
		if (ch == 'W')
			set->see.x = -1;
		if (ch == 'E')
			set->see.x = 1;
	}
	else
		exxxit(set, 1, "player position failure");
}

static void	validation(t_config *set, int x, int y)
{
	if (x == 0 || y == 0 || x >= (int)(ft_strlen(set->map[y]) - 1) || \
												y >= (set->lenymap - 1))
		exxxit(set, 1, "map error");
	if (!set->map[y - 1][x - 1] || set->map[y - 1][x - 1] == ' ' || \
			x >= (int)ft_strlen(set->map[y - 1]) - 1 || \
				set->map[y - 1][x] == ' ' || \
			!set->map[y - 1][x + 1] || set->map[y - 1][x + 1] == ' ' || \
			!set->map[y][x - 1] || set->map[y][x - 1] == ' ' || \
			!set->map[y][x + 1] || set->map[y][x + 1] == ' ' || \
			!set->map[y + 1][x - 1] || set->map[y + 1][x - 1] == ' ' || \
			x >= (int)ft_strlen(set->map[y + 1]) - 1 || \
				set->map[y + 1][x] == ' ' || \
			!set->map[y + 1][x + 1] || set->map[y + 1][x + 1] == ' ')
		exxxit(set, 1, "map error");
}

void		run_n_get(t_config *set)
{
	int		x;
	int		y;
	char	ch;

	y = -1;
	while (set->map[++y])
	{
		x = -1;
		while ((ch = set->map[y][++x]))
		{
			if (!ft_strchr("012 NSWE", ch))
				exxxit(set, 1, "prohibited symbols");
			if (ch == '2')
				set->count_sp++;
			if (ft_strchr("NSWE", ch))
				get_pos(set, x, y, ch);
			if (ft_strchr("02NSWE", ch))
				validation(set, x, y);
		}
	}
	if (set->plr.x < 0 || set->plr.y < 0)
		exxxit(set, 1, "player position failure");
	get_sprites(set);
}
