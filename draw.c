/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudakov <vrudakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:50:37 by vrudakov          #+#    #+#             */
/*   Updated: 2017/06/01 19:53:15 by vrudakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_put_pixel(int x, int y, int col, t_env *e)
{
	if (x < W && y < H && x >= 0 && y >= 0)
	{
		e->data[(x * (e->bpp / 8)) + (y * e->sl) + BLUE] = col & 0x0000FF;
		e->data[(x * (e->bpp / 8)) + (y * e->sl) + GREEN] = (col >> 8) & 0x00FF;
		e->data[(x * (e->bpp / 8)) + (y * e->sl) + RED] = col >> 16;
	}
}

void	drawline(t_ln ln, t_env *e)
{
	t_draw	d;

	d.delta_x = abs(ln.x2 - ln.x1);
	d.delta_y = abs(ln.y2 - ln.y1);
	d.sign_x = ln.x1 < ln.x2 ? 1 : -1;
	d.sign_y = ln.y1 < ln.y2 ? 1 : -1;
	d.error = d.delta_x - d.delta_y;
	my_put_pixel(ln.x2, ln.y2, 0x40E0D0, e);
	while (ln.x1 != ln.x2 || ln.y1 != ln.y2)
	{
		my_put_pixel(ln.x1, ln.y1, ln.col1, e);
		d.error2 = d.error * 2;
		if (d.error2 > -d.delta_y)
		{
			d.error -= d.delta_y;
			ln.x1 += d.sign_x;
		}
		if (d.error2 < d.delta_x)
		{
			d.error += d.delta_x;
			ln.y1 += d.sign_y;
		}
	}
}

void	set_middle(t_env *e)
{
	int x;
	int y;

	x = 0;
	while (x < e->map_y)
	{
		y = 0;
		while (y < e->map_x)
		{
			e->pnt[x][y].new_x += WC + e->off_x;
			e->pnt[x][y].new_y += HC + e->off_y;
			y++;
		}
		x++;
	}
}

void	draw_lines_x(t_env *e)
{
	int		w;
	int		h;
	t_ln	ln;

	h = 0;
	while (h < e->map_y)
	{
		w = 0;
		while (w < e->map_x)
		{
			ln.x1 = e->pnt[h][w].new_x;
			ln.y1 = e->pnt[h][w].new_y;
			ln.col1 = e->pnt[h][w].col;
			if (w + 1 < e->map_x)
			{
				ln.x2 = e->pnt[h][w + 1].new_x;
				ln.y2 = e->pnt[h][w + 1].new_y;
				ln.col2 = e->pnt[h][w + 1].col;
				drawline(ln, e);
			}
			w++;
		}
		h++;
	}
}

void	draw_lines_y(t_env *e)
{
	int		w;
	int		h;
	t_ln	ln;

	h = 0;
	while (h < e->map_y)
	{
		w = 0;
		while (w < e->map_x)
		{
			ln.x1 = e->pnt[h][w].new_x;
			ln.y1 = e->pnt[h][w].new_y;
			ln.col1 = e->pnt[h][w].col;
			if (h + 1 < e->map_y)
			{
				ln.x2 = e->pnt[h + 1][w].new_x;
				ln.y2 = e->pnt[h + 1][w].new_y;
				ln.col2 = e->pnt[h + 1][w].col;
				drawline(ln, e);
			}
			w++;
		}
		h++;
	}
}
