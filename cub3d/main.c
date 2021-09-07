/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:10:29 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:10:30 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void	free_some(t_config *set)
{
	if (set->no_tex.path)
		free(set->no_tex.path);
	if (set->so_tex.path)
		free(set->so_tex.path);
	if (set->we_tex.path)
		free(set->we_tex.path);
	if (set->ea_tex.path)
		free(set->ea_tex.path);
	if (set->sp_tex.path)
		free(set->sp_tex.path);
}

int			exxxit(t_config *set, int err, char *msg)
{
	free_some(set);
	if (set->map)
		free(set->map);
	if (set->d_buff)
		free(set->d_buff);
	if (set->sps)
		free(set->sps);
	if (set->img)
		mlx_destroy_image(set->mlx, set->img);
	if (set->win)
		mlx_destroy_window(set->mlx, set->win);
	if (err)
	{
		printf("Error\n");
		if (*msg)
			printf("%s\n", msg);
	}
	exit(0);
}

static int	kostil(t_config *set)
{
	exxxit(set, 0, "");
	return (0);
}

static void	toloop(t_config *set)
{
	mlx_hook(set->win, 2, 1L << 0, key_hook, set);
	mlx_hook(set->win, 17, 0, kostil, set);
	mlx_loop_hook(set->mlx, for_loop, set);
	mlx_loop(set->mlx);
}

int			main(int ac, char **av)
{
	t_config	set;

	if (ac < 2 || ac > 3 || ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub", 4))
		exxxit(&set, 1, "invalid arguments");
	if (ac == 3)
	{
		if (ft_strlen(av[2]) == 6 && !ft_strncmp(av[2], "--save", 6))
		{
			set.s_flag = 1;
			init(&set, av[1]);
			rendering(&set);
			take_pic(&set);
			exxxit(&set, 0, "");
		}
		else
			exxxit(&set, 1, "invalid arguments");
	}
	set.s_flag = 0;
	init(&set, av[1]);
	set.win = mlx_new_window(set.mlx, set.w_resol, set.h_resol, "cub3D");
	toloop(&set);
}
