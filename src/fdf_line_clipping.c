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
** Checks to see if the line is within the window bounds
*/

static int	fdf_inbounds(t_line *lin, int max_x, int max_y)
{
	if (((lin->dx >= 0 && lin->start->x >= 0 && lin->end->x <= max_x) ||
			(lin->dx < 0 && lin->start->x <= max_x && lin->end->x >= 0)) &&
			((lin->dy >= 0 && lin->start->y >= 0 && lin->end->y <= max_y) ||
			(lin->dy < 0 && lin->start->y <= max_y && lin->end->y >= 0)))
		return (1);
	return (0);
}

/*
** fdf_calculate_border checks to see if the line intersects any of the borders,
** and changes the tbounds based on where the intersection occurs.
*/

static int	fdf_calculate_border(double *tbound, int *tdir)
{
	int	i;
	int border;

	i = 0;
	border = -1;
	while (i < 4)
	{
		if (tbound[i] >= tbound[4] && tbound[i] <= tbound[5])
		{
			if (!(tdir[i]))
				tbound[4] = tbound[i];
			else
				tbound[5] = tbound[i];
			border = i;
		}
		i++;
	}
	return (border);
}

/*
** fdf_calculate_tbound is a helper function for clip_coordinates (it calculates
** the t values for each boundary)
*/

static int	fdf_calculate_tbound(double *tbound, int *tdir,
		t_line *lin, t_canvas *c)
{
	if (lin->dx)
		tbound[0] = -1 * (double)lin->start->x / (double)lin->dx;
	if (lin->dx)
		tbound[1] = (double)(c->s_x - lin->start->x) / (double)lin->dx;
	if (lin->dy)
		tbound[2] = -1 * (double)lin->start->y / (double)lin->dy;
	if (lin->dy)
		tbound[3] = (double)(c->s_y - lin->start->y) / (double)lin->dy;
	tdir[0] = (lin->dx > 0 ? 0 : 1);
	tdir[1] = (lin->dx < 0 ? 0 : 1);
	tdir[2] = (lin->dy > 0 ? 0 : 1);
	tdir[3] = (lin->dy < 0 ? 0 : 1);
	return (fdf_calculate_border(tbound, tdir));
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
** tbound[4] = minimum value of t;
** tbound[5] = maximum value of t;
**
** direction == 0: line is entering
** direction == 1: line is exiting
*/

int			fdf_clip_coordinates(t_canvas *c, t_line *lin)
{
	double	tbound[6];
	int		tdir[4];
	int		border;

//	if (lin->end->x <= c->s_x && lin->start->x >= 0 &&
//		lin->end->y <= c->s_y && lin->start->y >= 0)
//		return (1);
	tbound[0] = -1;
	tbound[1] = -1;
	tbound[2] = -1;
	tbound[3] = -1; 
	tbound[4] = 0;
	tbound[5] = 1;
	border = fdf_calculate_tbound(tbound, tdir, lin, c);
	lin->end->x = (int)(lin->start->x + (double)lin->dx * tbound[5]);
	lin->end->y = (int)(lin->start->y + (double)lin->dy * tbound[5]);
	lin->start->x = (int)(lin->start->x + (double)lin->dx * tbound[4]);
	lin->start->y = (int)(lin->start->y + (double)lin->dy * tbound[4]);
	return (fdf_inbounds(lin, c->s_x, c->s_y));
//	return (border == -1 ? 0 : 1);
}
