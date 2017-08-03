/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudakov <vrudakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:04:33 by vrudakov          #+#    #+#             */
/*   Updated: 2017/06/02 19:15:45 by vrudakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_x(void *param)
{
	param = NULL;
	exit(1);
}

void	init_e(t_env *e)
{
	int		end;

	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, W, H, "FDF");
	e->img = mlx_new_image(e->mlx, W, H);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->sl), &(end));
	e->set = 50;
	e->angle_z = 30;
	e->angle_x = 10;
	e->angle_y = 20;
	e->off_x = 0;
	e->off_y = 0;
	e->rise = 1;
	e->anim = 0;
	e->help = 0;
}

void	write_point(char *split, int i, t_env *e)
{
	e->pnt[e->map_y][i].pos_x = i;
	e->pnt[e->map_y][i].pos_y = e->map_y;
	e->pnt[e->map_y][i].z = ft_atoi(split);
	if (ft_strchr(split, ','))
		e->pnt[e->map_y][i].col = ft_atoi_base(ft_strchr(split, ',') + 1);
	else
		e->pnt[e->map_y][i].col = 0x40E0D0;
}

void	count_x(char *line, t_env *e)
{
	static int	x = 0;
	char		**split;
	int			i;

	split = ft_strsplit(line, ' ');
	i = 0;
	while (split[i])
	{
		write_point(split[i], i, e);
		i++;
	}
	if (i < x)
		x = i;
	else if (x == 0)
		x = i;
	e->map_x = x;
}

void	get_input(int argc, char **argv, t_env *e)
{
	char	*line;
	int		fd;
	char	**fdf;

	if (argc != 2)
	{
		write(1, "usage: sourcefile\n", 18);
		exit(EXIT_FAILURE);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit(write(1, "error\n", 6));
	e->map_y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		count_x(line, e);
		e->map_y++;
		free(line);
	}
	fdf = (char**)malloc(sizeof(char*) * e->map_y);
	close(fd);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit(write(1, "error\n", 6));
	fdf[e->map_y - 1] = NULL;
}
