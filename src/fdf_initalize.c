/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:05:48 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/30 17:50:39 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>

/*
** fdf_initalize_draw starts the process for drawing the image.
*/

/*
** Prototype function for drawing a line to an image and putting that image 
** to a window
*/
/*
void	draw_line(t_canvas *c, t_vector *start, t_vector *end)
{
	t_pixel	p;
}
*/


/*
** Take array of nodes, and image sketch. (change the z elevation point to the
** sketch coordinate of each node.)
** z = (formula to calculate the sketch address, would use)
**	NODES coord				SKTCH coord
**		x						(bpp / 8) * x
**		w * y					(sl * y)
**		z						formula
*/

/*void	fdf_draw_image(t_canvas *c, int x, int y)
{
	t_vector start;
	t_vector right;
	t_vector bottom;
}*/


/*	ft_printmap(&c->map);///
static void		ft_printmap(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
			ft_printf("%3d ",map->nods[(y * map->w) + x++].z);
		ft_printf("\n");
		y++;
	}
}*/

/*
** Calculate_img_offset calculates the appropriate distance between nodes to
** ensure that the map fits within the image, as well as the offset of the start
** of the map compared to the start of the image.
*/

void	calculate_img_offset(t_canvas *c)
{
	c->img.ctr = (c->s_y / 2) * c->img.sl + c->img.sl / 2;
}

/*
void	initalize_matrix(t_canvas *c)
{
	int		x;
	int		y;
	int		i;

	calculate_img_offset(c);
	y = 0;
	while (y < c->map.h)
	{
		x = 0;
		while (x < c->map.w)
		{
			index = y * c->map.w + x;
			c->map.nods[index].x = x * c->img.scale;
			c->map.nods[index].y = y * c->img.scale;
			c->map.nods[index].z *= c->img.scale;
			x++;
		}
		y++;
	}
}
*/

void	fdf_initialize_draw(char *file, t_canvas *c)
{
	EGUARD(get_data(file, c));
	c->mlx = mlx_init();
	EGUARD((c->img.id = mlx_new_image(c->mlx, c->s_x, c->s_y)));
	c->img.skt = mlx_get_data_addr
		(c->img.id, &c->img.bpp, &c->img.sl, &c->img.end);
/*
	EGUARD(initalize_matrix(c));
	fdf_draw_image(c, 0, 0);
	draw_line(c);
*/
	EGUARD((c->win = mlx_new_window(c->mlx, c->s_x, c->s_y, "fdf")));
	mlx_put_image_to_window(c->mlx, c->win, c->img.id, 10, 0);
}
