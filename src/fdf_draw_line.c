/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:19:57 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/06 15:37:05 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>

/*
** fdf_get_color retrieves the color for the specified pixel
*/

static void	fdf_get_color(t_pixel *cp, t_pixel *start, t_pixel *end)
{
	float	dx;
	float	dy;
	float	elevation;

	dx = end->x - start->x;
	dy = end->y - start->y;
}

/*
** fdf_draw_vertical is used to draw vertical lines (which would cause issues
** for the Bresenham's algorithm)
*/

/*static void	fdf_draw_vertical(t_pixel *start, t_pixel *end, t_canvas *c)
{
	t_pixel pix;

	pix.y = start->y;
	pix.x = start->x;
	while (pix.y < end->y)
	{
		pix.color = (pix.y - end->y)start->color;
		pixel_to_img(c, pix);
		pix.y++;
	}
}*/

/*
** fdf_draw_line uses the Bresenham's line algorithm to draw from pixel
** this specific algorithm is desgined to work with integer math for
** determining when to move along the vertical axis.
*/

void		fdf_draw_line(t_pixel *start, t_pixel *end, t_canvas *c)
{
	int		delta_y;
	int		delta_x;
	int		error;
	t_pixel	pix;

	pix.y = start->y;
	pix.x = start->x - 1;
	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	error = 2 * (delta_y - delta_x);
	while (++pix.x < end->x)
	{
		pix.color = start->color;
		pixel_to_img(c, pix);
		if (error > 0)
		{
			pix.y++;
			error -= delta_x;
		}
		error +=delta_y;
	}
}

/*
** fdf_switch_octants is used to establish which coordinate is the starting
** coordinate and which one is the ending coordinate based on.
*/

void	fdf_switch_octants(int octant, t_pixel *p1, t_pixel *p2, t_canvas *c)
{
	t_pixel	ip1;
	t_pixel	ip2;

	ip1.x = p1->y;
	ip1.y = p1->x;
	ip1.color = p1->color;
	ip2.x = p2->y;
	ip2.y = p2->x;
	ip2.color = p2->color;
	if (octant == 0)
		fdf_draw_line(p1, p2, c);
	else if (octant == 1)
		fdf_draw_line(ip1, ip2, c);
	else if (octant == 2)
	else if (octant == 3)
	else if (octant == 4)
		fdf_draw_line(p2, p1, c);
	else if (octant == 5)
	else if (octant == 6)
	else if (octant == 7)
}
