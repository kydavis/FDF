/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line_clipping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:48:01 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/11 15:52:23 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
** fdf_calculate_tbound is a helper function for clip_coordinates (it calculates
** the t values for each boundary)
*/

static int	fdf_calculate_tbound(float *tbound, int *tdir,
		t_line *lin, t_canvas *c)
{
	int	i;

	if (lin->dx)
		tbound[0] = -1 * (float)lin->start->x / (float)lin->dx;
	if (lin->dx)
		tbound[1] = (float)(c->s_x - lin->start->x) / (float)lin->dx;
	if (lin->dy)
		tbound[2] = -1 * (float)lin->start->y / (float)lin->dy;
	if (lin->dy)
		tbound[3] = (float)(c->s_y - lin->start->y) / (float)lin->dy;
	tdir[0] = (-lin->dx < 0 ? 0 : 1);
	tdir[1] = (lin->dx < 0 ? 0 : 1);
	tdir[2] = (-lin->dy < 0 ? 0 : 1);
	tdir[3] = (lin->dy < 0 ? 0 : 1);
	i = ~0;
	while (++i < 4 && lin->dx && lin->dy)
		if (tbound[i] >= tbound[4] && tbound[i] <= tbound[5])
		{
			if (!(tdir[i]))
				tbound[4] = tbound[i];
			else
				tbound[5] = tbound[i];
			return (i);
		}
	return (-1);
}

/*
** fdf_clip_coordinates clips the coordinate boundaries to ensure that excess
** processing is not used for "drawing lines" offscreen.
** Makes use of the parametric equation of a line segment:
**		(x, y) = (x1, y1) + t * (dx, dy);
** tbound[0] = Left boundary
** tbound[1] = Right boundary
** tbound[2] = Top boundary
** tbound[3] = Bottom boundary
** tbound[4] = tmin;
** tbound[5] = tmax;
** t[0] = minimum value of t.
** t[1] = maximum value of t.
**
** direction == 0: line is entering
** direction == 1: line is exiting
*/

int			fdf_clip_coordinates(t_canvas *c, t_line *lin)
{
	float	tbound[6];
	int		tdir[4];
	int		border;

	tbound[4] = 0;
	tbound[5] = 1;
	border = fdf_calculate_tbound(tbound, tdir, lin, c);
	lin->end->x = (int)(lin->start->x + (float)lin->dx * tbound[5]);
	lin->end->y = (int)(lin->start->y + (float)lin->dy * tbound[5]);
	lin->start->x = (int)(lin->start->x + (float)lin->dx * tbound[4]);
	lin->start->y = (int)(lin->start->y + (float)lin->dy * tbound[4]);
	return (1);
}
