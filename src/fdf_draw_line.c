/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:19:57 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/10 12:43:35 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <math.h>

/*
** fdf_get_color retrieves the color for the specified pixel
*/

static void	fdf_get_color(t_pixel *cp, t_pixel *start, t_pixel *end)
{
	int		color;
	int		sdx;
	int		edx;

	sdx = cp->x - start->x;
	edx = end->x - cp->x;
	color = (sdx > edx ? end->color : start->color);
	cp->color = color;
}

/*
** fdf_plot_pixel switches the output to appropriate octant and retrieves
** the color the pixel is supposed to display.
*/

static void	fdf_plot_point(t_canvas *c, t_pixel *cp, t_pixel *sp, t_pixel *ep)
{
	t_pixel	print_pix;

	print_pix.x = cp->x;
	print_pix.y = cp->y;
	fdf_get_color(&print_pix, sp, ep);
/*ft_printf("\nBefore swap coordinates (x,y) (%d, %d)", print_pix.x, print_pix.y);*/
	if (c->octant > 2 && c->octant < 7)
		print_pix.x = -cp->x;
	if (c->octant == 2 || (c->octant > 3 && c->octant != 6))
		print_pix.y = -cp->y;
	if (c->octant == 1 || c->octant == 2 || c->octant == 5 || c->octant == 6)
		ft_xorswapi(&print_pix.x, &print_pix.y);
/*ft_printf("\nAfter swap coordinates (x,y) (%d, %d)\n", print_pix.x, print_pix.y);*/
	pixel_to_img(c, &print_pix);
}

/*
** fdf_draw_line uses the Bresenham's line algorithm to draw from pixel
** this specific algorithm is desgined to work with integer math for
** determining when to move along the vertical axis.
*/

static void		fdf_bress_line(t_pixel *start, t_pixel *end, t_canvas *c)
{
	int		delta_y;
	int		delta_x;
	int		error;
	t_pixel	pix;

	pix.y = start->y;
	pix.x = start->x;
	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	error = 2 * (delta_y - delta_x);
	while (pix.x < end->x)
	{
/*		ft_printf("\ncoordinates (x,y) (%d, %d)", pix.x, pix.y);*/
		fdf_plot_point(c, &pix, start, end);
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
** fdf_clip_coordinates clips the coordinate boundaries to ensure that excess
** processing is not used for "drawing lines" offscreen.
** Makes use of the parametric equation of a line segment:
**		(x, y) = (x1, y1) + t * (dx, dy);
** tbound[0] = Left boundary
** tbound[1] = Right boundary
** tbound[2] = Top boundary
** tbound[3] = Bottom boundary
** t[0] = minimum value of t.
** t[1] = maximum value of t.
**
** direction == 0: line is entering
** direction == 1: line is exiting
*/

int		fdf_clip_coordinates(t_pixel *p1, t_pixel *p2, t_canvas *c)
{
	float	tbound[4];
	float	t[2];
	int		tdir[5];
	int		dx;
	int		dy;

	t[0] = 0;
	t[1] = 1;
	if ((dx = p2->x - p1->x))
	{
		tbound[0] = -1 * (float)p1->x / dx;
		tdir[0] = (-dx < 0 ? 0 : 1);
		tbound[1] = (float)(c->s_x - p1->x) / dx;
		tdir[1] = (dx < 0 ? 0 : 1);
	}
	if ((dy = p2->y - p1->y))
	{
		tbound[2] = -1 * (float)p1->y / dy;
		tdir[2] = (-dy < 0 ? 0 : 1);
		tbound[3] = (float)(c->s_y - p1->y) / dy;
		tdir[3] = (dy < 0 ? 0 : 1);
	}
	tdir[4] = ~0;
	while (++tdir[4] < 4)
		if (tbound[tdir[4]] >= t[0] && tbound[tdir[4]] <= t[1])
		{
			if (tdir[tdir[4]])
				t[0] = tbound[tdir[4]];
			else
				t[1] = tbound[tdir[4]];
		}
	p1->x = (int)(p1->x + dx * t[0]);
	p1->y = (int)(p1->y + dy * t[0]);
	p2->x = (int)(p1->x + dx * t[1]);
	p2->y = (int)(p1->y + dy * t[1]);
	return (0);
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
	int		dcord[2];
	int		quad;

/*	if (p1.x >= c->s_x || p1.x < 0 || p1.y >= c->s_y || p1.y < 0 ||
			p2.x >= c->s_x || p2.x < 0 || p2.y >= c->s_y || p2.y < 0)
		if (!fdf_clip_coordinates(&p1, &p2, c))
			return ;*/
	dcord[0] = p2.x - p1.x;
	if ((dcord[1] = p2.y - p1.y) >= 0)
		quad = (dcord[0] >= 0 ? 0 : 1);
	else
		quad = (dcord[0] >= 0 ? 3 : 2);
	dcord[1] = (int)ft_absolute(dcord[1]);
	dcord[0] = (int)ft_absolute(dcord[0]);
	if (quad == 0)
		c->octant = (dcord[0] > dcord[1] ? 0 : 1);
	else if (quad == 1)
		c->octant = (dcord[0] > dcord[1] ? 3 : 2);
	else if (quad == 2)
		c->octant = (dcord[0] > dcord[1] ? 4 : 5);
	else if (quad == 3)
		c->octant = (dcord[0] > dcord[1] ? 7 : 6);
	fdf_octant_switch(c->octant, &p1);
	fdf_octant_switch(c->octant, &p2);
	fdf_bress_line(&p1, &p2, c);
}
