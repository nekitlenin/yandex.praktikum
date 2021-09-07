/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:08 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 15:20:44 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static void	write_n_clear(t_config *set, t_list **head)
{
	t_list	*temp;
	int		i;

	set->map = ft_calloc(1 + set->lenymap, sizeof(char *));
	i = -1;
	while (*head)
	{
		set->map[++i] = (*head)->content;
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void		get_map(t_config *set, int fd)
{
	t_list	*head;
	char	*line;
	int		test;

	head = NULL;
	line = NULL;
	while ((test = get_next_line(fd, &line)) && !ft_strlen(line))
		free(line);
	ft_lstadd_back(&head, ft_lstnew(line));
	while (get_next_line(fd, &line))
	{
		if (!ft_strlen(line))
			exxxit(set, 1, "invalid map");
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	set->lenymap = ft_lstsize(head);
	write_n_clear(set, &head);
}

static void	textures_init(t_config *set)
{
	if (!(set->no_tex.img = mlx_xpm_file_to_image(set->mlx, \
						set->no_tex.path, &set->no_tex.w, &set->no_tex.h)))
		exxxit(set, 1, "texture failure");
	if (!(set->so_tex.img = mlx_xpm_file_to_image(set->mlx, \
						set->so_tex.path, &set->so_tex.w, &set->so_tex.h)))
		exxxit(set, 1, "texture failure");
	if (!(set->we_tex.img = mlx_xpm_file_to_image(set->mlx, \
						set->we_tex.path, &set->we_tex.w, &set->we_tex.h)))
		exxxit(set, 1, "texture failure");
	if (!(set->ea_tex.img = mlx_xpm_file_to_image(set->mlx, \
						set->ea_tex.path, &set->ea_tex.w, &set->ea_tex.h)))
		exxxit(set, 1, "texture failure");
	if (!(set->sp_tex.img = mlx_xpm_file_to_image(set->mlx, \
						set->sp_tex.path, &set->sp_tex.w, &set->sp_tex.h)))
		exxxit(set, 1, "texture failure");
	set->no_tex.addr = mlx_get_data_addr(set->no_tex.img, &set->no_tex.bpp, \
											&set->no_tex.len, &set->no_tex.end);
	set->so_tex.addr = mlx_get_data_addr(set->so_tex.img, &set->so_tex.bpp, \
											&set->so_tex.len, &set->so_tex.end);
	set->we_tex.addr = mlx_get_data_addr(set->we_tex.img, &set->we_tex.bpp, \
											&set->we_tex.len, &set->we_tex.end);
	set->ea_tex.addr = mlx_get_data_addr(set->ea_tex.img, &set->ea_tex.bpp, \
											&set->ea_tex.len, &set->ea_tex.end);
	set->sp_tex.addr = mlx_get_data_addr(set->sp_tex.img, &set->sp_tex.bpp, \
											&set->sp_tex.len, &set->sp_tex.end);
}

void		init(t_config *set, char *map_path)
{
	set->count_sp = 0;
	set->see.x = 0;
	set->see.y = 0;
	set->plr.x = -1;
	set->plr.y = -1;
	set->w_resol = -1;
	set->h_resol = -1;
	set->f_color = -1;
	set->c_color = -1;
	set->lenymap = 0;
	parser(set, map_path);
	set->mlx = mlx_init();
	set->img = mlx_new_image(set->mlx, set->w_resol, set->h_resol);
	set->addr = mlx_get_data_addr(set->img, &set->bpp, &set->l_len, &set->end);
	textures_init(set);
	set->d_buff = malloc(sizeof(double) * set->w_resol);
}
