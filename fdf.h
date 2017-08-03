/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudakov <vrudakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:42:27 by vrudakov          #+#    #+#             */
/*   Updated: 2017/06/02 19:14:35 by vrudakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
# define FDF_FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <limits.h>
# include <math.h>
# include "mlx.h"

# define RED 2
# define GREEN 1
# define BLUE 0
# define W 1200
# define H 800
# define HC H/2
# define WC W/2
# define PI 3.14159265359
# define COSN(angle) cos(angle * PI / 180)
# define SINS(angle) sin(angle * PI / 180)

typedef struct	s_ln
{
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		col1;
	int		col2;
}				t_ln;

typedef struct	s_pnt
{
	int		pos_x;
	int		pos_y;
	int		z;
	int		new_z;
	int		new_x;
	int		new_y;
	int		col;

}				t_pnt;

typedef struct	s_draw
{
	int		delta_x;
	int		delta_y;
	int		sign_x;
	int		sign_y;
	int		error;
	int		error2;

}				t_draw;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;

	int		map_y;
	int		map_x;
	int		off_x;
	int		off_y;

	char	*data;
	int		sl;
	int		bpp;
	float	set;
	int		angle_z;
	int		angle_x;
	int		angle_y;
	double	rise;
	int		anim;
	int		help;
	t_pnt	pnt[2000][2000];
}				t_env;

int				ft_atoi_base(char *str);
void			my_put_pixel(int x, int y, int col, t_env *e);
void			get_input(int argc, char **argv, t_env *e);
void			draw_lines_x(t_env *e);
void			draw_lines_y(t_env *e);
void			set_middle(t_env *e);
void			init_e(t_env *e);
void			rotate_z(t_env *data);
void			rotate_x(t_env *data);
void			rotate_y(t_env *data);

int				my_key_funct(int keycode, t_env *e);
void			my_key_pt2(int keycode, t_env *e);

int				exit_x(void *par);
void			volume(t_env *e);
void			set_middle(t_env *e);
void			scale(t_env *e);
void			drawline(t_ln ln, t_env *e);

#endif
