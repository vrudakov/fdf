/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudakov <vrudakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:54:51 by vrudakov          #+#    #+#             */
/*   Updated: 2017/06/01 19:55:06 by vrudakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_env *e)
{
	int		x;
	int		y;

	x = 0;
	while (x < e->map_y)
	{
		y = 0;
		while (y < e->map_x)
		{
			e->pnt[x][y].new_x = e->pnt[x][y].pos_x * e->set;
			e->pnt[x][y].new_y = e->pnt[x][y].pos_y * e->set;
			y++;
		}
		x++;
	}
}

void	volume(t_env *e)
{
	int		x;
	int		y;

	x = 0;
	while (x < e->map_y)
	{
		y = 0;
		while (y < e->map_x)
		{
			e->pnt[x][y].new_x -= ((e->map_x * e->set) / 2);
			e->pnt[x][y].new_y -= ((e->map_y * e->set) / 2);
			y++;
		}
		x++;
	}
}

void	rotate_x(t_env *e)
{
	int		x;
	int		y;
	int		ty;

	x = 0;
	while (x < e->map_y)
	{
		y = 0;
		while (y < e->map_x)
		{
			ty = e->pnt[x][y].new_y;
			e->pnt[x][y].new_y = round(ty * COSN(e->angle_x) - e->pnt[x][y].z *
				e->rise * SINS(e->angle_x));
			e->pnt[x][y].new_z = round(-ty * SINS(e->angle_x) - e->pnt[x][y].z *
				e->rise * COSN(e->angle_x));
			y++;
		}
		x++;
	}
}

void	rotate_y(t_env *e)
{
	int		x;
	int		y;
	int		tx;

	x = 0;
	while (x < e->map_y)
	{
		y = 0;
		while (y < e->map_x)
		{
			tx = e->pnt[x][y].new_x;
			e->pnt[x][y].new_x = round(tx * COSN(e->angle_y) +
				e->pnt[x][y].new_z * SINS(e->angle_y));
			e->pnt[x][y].new_z = round(-tx * SINS(e->angle_y) +
				e->pnt[x][y].new_z * COSN(e->angle_y));
			y++;
		}
		x++;
	}
}

void	rotate_z(t_env *e)
{
	int		x;
	int		y;
	int		tx;
	int		ty;

	x = 0;
	while (x < e->map_y)
	{
		y = 0;
		while (y < e->map_x)
		{
			tx = e->pnt[x][y].new_x;
			ty = e->pnt[x][y].new_y;
			e->pnt[x][y].new_x = round(tx * COSN(e->angle_z) - ty *
				SINS(e->angle_z));
			e->pnt[x][y].new_y = round(tx * SINS(e->angle_z) + ty *
				COSN(e->angle_z));
			y++;
		}
		x++;
	}
}
