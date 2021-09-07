/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:10:55 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:10:55 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static int	counter(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (line[++i])
	{
		if (!ft_strchr("+0123456789 ,", line[i]))
			return (0);
		if (line[i] == ',')
			count++;
	}
	return (count);
}

void		check_color_format(t_config *set, char *line)
{
	int	i;
	int	count;

	count = counter(line);
	if (count != 2)
		exxxit(set, 1, "1wrong color format");
	i = 0;
	while (count >= 0)
	{
		while (line[i] == ' ' || line[i] == '+')
			i++;
		if (!ft_isdigit(line[i]))
			exxxit(set, 1, "2wrong color format");
		while (ft_isdigit(line[i]))
			i++;
		while (count != 0 && line[i] == ' ')
			i++;
		if (count != 0 && line[i++] != ',')
			exxxit(set, 1, "wrong color format");
		if (count == 0 && line[i] != '\0')
			exxxit(set, 1, "wrong color format");
		count--;
	}
}

int			check_resol_line(int i, char *line)
{
	while (line[i])
	{
		if (!ft_strchr("0 123456789", line[i]))
			return (0);
		i++;
	}
	return (1);
}
