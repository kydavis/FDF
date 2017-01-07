/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:19:57 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/06 20:54:58 by kdavis           ###   ########.fr       */
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
	double	color;
	float	tdx;
	float	sdx;
	float	edx;

	tdx = end->x - start->x;
	sdx = cp->x - start->x;
	edx = end->x - cp->x;
	color = (sdx / tdx) * (float)end->color + (edx / tdx) * (float)start->color;
	cp->color = (int)color;
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
	if (c->octant > 2 && c->octant < 7)
		print_pix.x = -cp->x;
	if (c->octant == 2 || c->octant > 3)
		print_pix.y = -cp->y;
	if (c->octant == 1 || c->octant == 2 || c->octant == 5 || c->octant == 6)
		ft_xorswapi(&print_pix.x, &print_pix.y);
	pixel_to_img(c, &print_pix);
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
/*		ft_printf("\nstart: (%d, %d) end: (%d, %d)", start->x, start->y, end->x,
				end->y);///
		ft_printf("\ncoordinates (x,y) (%d, %d)", pix.x, pix.y);*/
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
	int	temp;

/*	ft_printf("\nfdf_octant_switch\n");///
	ft_printf("octant:%d before: cp->x: %d, cp->y:%d\n",oct, cp->x, cp->y);*/
	if (oct > 1 && oct < 6)
		cp->x = -cp->x;
	if (oct > 3)
		cp->y = -cp->y;
	if (oct == 1 || oct == 2 || oct == 5 || oct == 6)
	{
		temp = cp->x;
		cp->x = cp->y;
		cp->y = temp;
	}
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
	int		dcord[2];
	float	angle;
	int		quad;

	dcord[0] = p2.x - p1.x;
	dcord[1] = p2.y - p1.y;
	angle = asin(dcord[1]);
	if (dcord[1] >= 0)
		quad = (dcord[0] >= 0 ? 0 : 1);
	else
		quad = (dcord[0] >= 0 ? 2 : 3);
	if (quad == 0)
		c->octant = (angle <= M_PI_4 ? 0 : 1);
	else if (quad == 1)
		c->octant = (angle <= M_PI_4 ? 2 : 3);
	else if (quad == 2)
		c->octant = (angle >= -M_PI_4 ? 4 : 5);
	else if (quad == 3)
		c->octant = (angle >= -M_PI_4 ? 7 : 6);
	fdf_octant_switch(c->octant, &p1);
	fdf_octant_switch(c->octant, &p2);
	fdf_bress_line(&p1, &p2, c);
}
