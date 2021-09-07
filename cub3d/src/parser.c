/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:11:18 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:11:18 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static int	get_path(int bit_code, char **var, char *line)
{
	*var = ft_strtrim(line, " ");
	return (bit_code);
}

static int	get_resolution(int i, t_config *set, char *line)
{
	int	def_w;
	int	def_h;

	if (!check_resol_line(i, line))
		return (0);
	mlx_get_screen_size(&def_w, &def_h);
	set->w_resol = ft_atoi(&line[i]) & 0xffffff;
	set->w_resol = set->w_resol > 10240 ? 10240 : set->w_resol;
	if (!set->s_flag && set->w_resol > def_w)
		set->w_resol = def_w;
	while (line[i] == ' ' || line[i] == '+')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	set->h_resol = ft_atoi(&line[i]) & 0xffffff;
	set->h_resol = set->h_resol > 5760 ? 5760 : set->h_resol;
	if (!set->s_flag && set->h_resol > def_h)
		set->h_resol = def_h;
	while (line[i] == ' ' || line[i] == '+')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0' || set->w_resol <= 0 || set->h_resol <= 0)
		return (0);
	return (0x800);
}

static int	get_color(int bit_code, t_config *set, int *color, char *line)
{
	int i;
	int	temp;

	check_color_format(set, line);
	i = 0;
	if ((temp = ft_atoi(line)) > 255)
		return (0);
	*color = temp << 16;
	while (line[i] != ',')
		i++;
	if ((temp = ft_atoi(&line[++i])) > 255)
		return (0);
	*color = *color | temp << 8;
	while (line[i] != ',')
		i++;
	if ((temp = ft_atoi(&line[++i])) > 255)
		return (0);
	*color = *color | temp;
	return (*color < 0) ? 0 : bit_code;
}

static int	get_settings(int *n, t_config *set, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		*n = *n + get_resolution(i + 1, set, line);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		*n = *n + get_path(0x400, &set->no_tex.path, &line[i + 2]);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		*n = *n + get_path(0x200, &set->so_tex.path, &line[i + 2]);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		*n = *n + get_path(0x100, &set->we_tex.path, &line[i + 2]);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		*n = *n + get_path(0x80, &set->ea_tex.path, &line[i + 2]);
	else if (line[i] == 'S' && line[i + 1] != 'O')
		*n = *n + get_path(0x40, &set->sp_tex.path, &line[i + 1]);
	else if (line[i] == 'F')
		*n = *n + get_color(0x20, set, &set->f_color, &line[i + 1]);
	else if (line[i] == 'C')
		*n = *n + get_color(0x10, set, &set->c_color, &line[i + 1]);
	else
		exxxit(set, 1, "unknown key");
	return (1);
}

int			parser(t_config *set, char *map_path)
{
	int		fd;
	char	*line;
	int		n;
	int		z;

	line = NULL;
	if ((fd = open(map_path, O_RDONLY)) < 0)
		exxxit(set, 1, "opening failure");
	n = 0;
	while ((n & 0b1111) < 8 && (z = get_next_line(fd, &line)))
	{
		if (z == -1)
			exxxit(set, 1, "reading failure");
		if (ft_strlen(line))
			n += get_settings(&n, set, line);
		free(line);
	}
	if (n != 0xFF8)
		exxxit(set, 1, "wrong parameters");
	get_map(set, fd);
	run_n_get(set);
	close(fd);
	return (n);
}
