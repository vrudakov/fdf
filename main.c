/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudakov <vrudakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 20:06:37 by vrudakov          #+#    #+#             */
/*   Updated: 2017/06/02 19:16:07 by vrudakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	help(t_env *e)
{
	if (e->help == 0)
	{
		mlx_string_put(e->mlx, e->win, 5, 0, 0xffffff,
						"S - start/stop animation");
		mlx_string_put(e->mlx, e->win, 5, 15, 0xffffff,
						"H - open/close help");
		mlx_string_put(e->mlx, e->win, 5, 30, 0xffffff,
						"Arrows - change posotion");
		mlx_string_put(e->mlx, e->win, 5, 45, 0xffffff,
						"Rotation: x -'4', '5' y - '7' '8' z - '1' '2'");
		mlx_string_put(e->mlx, e->win, 5, 60, 0xffffff,
						"Change size + and - on numpad");
		mlx_string_put(e->mlx, e->win, 5, 75, 0xffffff,
						"Change bulk / and * on numpad");
	}
}

int		draw_all(t_env *e)
{
	scale(e);
	volume(e);
	rotate_x(e);
	rotate_y(e);
	rotate_z(e);
	set_middle(e);
	draw_lines_x(e);
	draw_lines_y(e);
	if (e->map_x == 1 && e->map_y == 1)
		my_put_pixel(WC + e->off_x, HC + e->off_y, e->pnt[0][0].col, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 3, 3);
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, W, H);
	help(e);
	if (e->anim == 1)
		e->angle_y += 1;
	return (0);
}

int		my_key_funct(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 69)
	{
		e->rise *= 1.1;
		e->set *= 1.2;
	}
	if (keycode == 78 && e->set > 0)
	{
		e->set *= 0.8;
		e->rise *= 0.9;
	}
	if (keycode == 83 || keycode == 18)
		e->angle_z++;
	if (keycode == 84 || keycode == 19)
		e->angle_z -= 5;
	if (keycode == 86 || keycode == 21)
		e->angle_x++;
	if (keycode == 87 || keycode == 23)
		e->angle_x -= 5;
	if (keycode == 89 || keycode == 26)
		e->angle_y++;
	my_key_pt2(keycode, e);
	return (0);
}

void	my_key_pt2(int keycode, t_env *e)
{
	if (keycode == 91 || keycode == 28)
		e->angle_y -= 5;
	if (keycode == 67)
		e->rise *= 1.1;
	if (keycode == 75)
		e->rise *= 0.9;
	if (keycode == 126)
		e->off_y -= 3;
	if (keycode == 125)
		e->off_y += 3;
	if (keycode == 123)
		e->off_x -= 3;
	if (keycode == 124)
		e->off_x += 3;
	if (keycode == 4)
		e->help = (e->help == 0) ? 1 : 0;
	if (keycode == 1)
		e->anim = (e->anim == 0) ? 1 : 0;
	draw_all(e);
}

int		main(int argc, char **argv)
{
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (!e)
		return (0);
	get_input(argc, argv, e);
	init_e(e);
	mlx_hook(e->win, 2, 5, my_key_funct, e);
	mlx_loop_hook(e->mlx, draw_all, e);
	mlx_hook(e->win, 17, 1L << 17, exit_x, &e);
	mlx_loop(e->mlx);
	free(e);
	return (1);
}
