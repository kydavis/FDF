/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:19:57 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/10 18:06:59 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <math.h>

/*
** fdf_calculate_tbound is a helper function for clip_coordinates (it calculates
** the t values for each boundary)
*/

static int		fdf_calculate_tbound(float *tbound, int *tdir,
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
			return(i);
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
#include <stdio.h>
int		fdf_clip_coordinates(t_canvas *c, t_line *lin)
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

/*
** fdf_plot_pixel switches the output to appropriate octant and retrieves
** the color the pixel is supposed to display.
*/

static void	fdf_plot_point(t_canvas *c, t_pixel *cp, t_line *l)
{
	t_pixel	print_pix;
	int		sdx;
	int		edx;

	sdx = cp->x - l->start->x;
	edx = l->end->x - cp->x;
	print_pix.x = cp->x;
	print_pix.y = cp->y;
	print_pix.color = (sdx > edx ? l->end->color : l->start->color);
/*ft_printf("\nBefore swap coordinates (x,y) (%d, %d)", print_pix.x, print_pix.y);*/
	if (l->octant > 2 && l->octant < 7)
		print_pix.x = -cp->x;
	if (l->octant == 2 || (l->octant > 3 && l->octant != 6))
		print_pix.y = -cp->y;
	if (l->octant == 1 || l->octant == 2 || l->octant == 5 || l->octant == 6)
		ft_xorswapi(&print_pix.x, &print_pix.y);
/*ft_printf("\nAfter swap coordinates (x,y) (%d, %d)\n", print_pix.x, print_pix.y);*/
	pixel_to_img(c, &print_pix);
}

/*
** fdf_draw_line uses the Bresenham's line algorithm to draw from pixel
** this specific algorithm is desgined to work with integer math for
** determining when to move along the vertical axis.
*/

static void		fdf_bress_line(t_canvas *c, t_line *line)
{
	int		delta_y;
	int		delta_x;
	int		error;
	t_pixel	pix;

	pix.y = line->start->y;
	pix.x = line->start->x;
	delta_x = line->end->x - line->start->x;
	delta_y = line->end->y - line->start->y;
	error = 2 * (delta_y - delta_x);
	while (pix.x < line->end->x)
	{
/*		ft_printf("\ncoordinates (x,y) (%d, %d)", pix.x, pix.y);*/
		fdf_plot_point(c, &pix, line);
		if (error > 0)
		{
			pix.y++;
			error -= delta_x;
		}
		error += delta_y;
		pix.x++;
	}
}

/*
** fdf_octant_switch adjusts the input coordinates for the Bresenham algorithm
*/

static void	fdf_octant_switch(int oct, t_pixel *cp)
{

/*	ft_printf("\nfdf_octant_switch\n");///
	ft_printf("octant:%d before: cp->x: %d, cp->y:%d\n",oct, cp->x, cp->y);*/
	if (oct > 1 && oct < 6)
		cp->x = -cp->x;
	if (oct > 3)
		cp->y = -cp->y;
	if (oct == 1 || oct == 2 || oct == 5 || oct == 6)
		ft_xorswapi(&cp->x, &cp->y);
/*	ft_printf("after: cp->x: %d, cp->y:%d\n",cp->x, cp->y);*/
}

/*
** fdf_switch_octant calculates what octant the pixels should be in and adjusts
** the coordinates appropriatley.
** The higher values of oct indicate
** dcord[0] = change in x coordinate between pixels
** dcord[1] = change in y coordinate between pixels
*/

void		fdf_draw_line(t_pixel p1, t_pixel p2, t_canvas *c)
{
	t_line	line;
	int		quad;

	line.dx = p2.x - p1.x;
	line.start = &p1;
	line.end = &p2;
	if ((line.dy = p2.y - p1.y) >= 0)
		quad = (line.dx >= 0 ? 0 : 1);
	else
		quad = (line.dx >= 0 ? 3 : 2);
	if (!fdf_clip_coordinates(c, &line))
		return ;
	line.dy = (int)ft_absolute(line.dy);
	line.dx = (int)ft_absolute(line.dx);
	if (quad == 0)
		line.octant = (line.dx > line.dy ? 0 : 1);
	else if (quad == 1)
		line.octant = (line.dx > line.dy ? 3 : 2);
	else if (quad == 2)
		line.octant = (line.dx > line.dy ? 4 : 5);
	else if (quad == 3)
		line.octant = (line.dx > line.dy ? 7 : 6);
	fdf_octant_switch(line.octant, &p1);
	fdf_octant_switch(line.octant, &p2);
	fdf_bress_line(c, &line);
}
