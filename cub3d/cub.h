/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyasuko <pyasuko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:10:41 by pyasuko           #+#    #+#             */
/*   Updated: 2021/03/23 12:10:41 by pyasuko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "gss.h"
# include "libft.h"
# define SCL 10
# define R90 asin(1)
# define L90 -asin(1)

typedef struct	s_tex
{
	char		*path;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	int			len;
	int			w;
	int			h;
}				t_tex;

typedef struct	s_vec {
	double		x;
	double		y;
}				t_vec;

typedef struct	s_sp
{
	t_vec		crd;
	t_vec		sp;
	double		len;
	double		dist;
	int			w;
	int			h;
	int			scr_ypos;
	double		tex_ypos;
	t_vec		sc_end;
}				t_sp;

typedef struct	s_ray {
	t_vec		pos;
	t_vec		dir;
	int			map_x;
	int			map_y;
	t_vec		step;
	int			side;
	double		dist_w;
	int			line_h;
}				t_ray;

typedef struct	s_config {
	t_tex		no_tex;
	t_tex		so_tex;
	t_tex		we_tex;
	t_tex		ea_tex;
	t_tex		sp_tex;
	char		**map;
	int			w_resol;
	int			h_resol;
	int			f_color;
	int			c_color;
	int			l_len;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	t_vec		see;
	t_vec		plane;
	t_vec		plr;
	t_ray		ray;
	int			count_sp;
	t_sp		*sps;
	double		*d_buff;
	int			lenymap;
	int			s_flag;
}				t_config;

typedef struct	s_valid
{
	t_config	*set;
	char		**map;
	t_vec		*arr;
	int			leny;
}				t_valid;

void			init(t_config *set, char *map_path);
int				parser(t_config *set, char *map_path);
int				rendering(t_config *set);
void			manipulation(t_config *set);
void			my_pixelput(t_config *set, int x, int y, int color);
void			draw_line(t_config *set, t_vec v1, t_vec v2, int color);
void			draw_vline(t_config *set, int x, t_vec pos, int color);
void			draw_2d_map(t_config *set);
t_vec			vec_sum(t_vec v1, t_vec v2, char act);
double			vec_len(t_vec v);
t_vec			vec_norm(t_vec v);
t_vec			vec_x(t_vec v, double n);
t_vec			vec_rot(t_vec v, double ang);
double			vec_mul(t_vec v1, t_vec v2);
void			cast(t_config *set, t_ray *ray);
int				key_hook(int keycode, t_config *set);
int				exxxit(t_config *set, int err, char *msg);
void			sprites(t_config *set);
int				take_pic(t_config *set);
int				for_loop(t_config *set);
void			validator(t_config *set);
void			get_map(t_config *set, int fd);
void			run_n_get(t_config *set);
void			check_color_format(t_config *set, char *line);
int				check_resol_line(int i, char *line);

#endif
