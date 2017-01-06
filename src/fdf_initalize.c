/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:05:48 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/05 12:44:59 by kdavis           ###   ########.fr       */
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
** Take array of nodes, and image sketch. (change the z elevation point to the
** sketch coordinate of each node.)
** z = (formula to calculate the sketch address, would use)
**	NODES coord				SKTCH coord
**		x						(bpp / 8) * x
**		w * y					(sl * y)
**		z						formula
*/

/*#include <stdio.h>///
static void		ft_printmap(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->h)
	{
		x = -1;
		while (++x < map->w)
			printf("%5.1f,%-5.1f",
					map->nods[(y * map->w) + x].x,
					map->nods[(y * map->w) + x].y);
		printf("\n");
		y++;
	}
}*/

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
