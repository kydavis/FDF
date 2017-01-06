/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:05:48 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/05 19:20:26 by kdavis           ###   ########.fr       */
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

#include <stdio.h>///
static void		ft_printmap(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->h)
	{
		x = -1;
		while (++x < map->w)
			printf("%10.1d,%-10.1d",
					map->twd[(y * map->w) + x].x,
					map->twd[(y * map->w) + x].y);
		printf("\n");
		y++;
	}
}

/*
** fdf_initialize_modifier initializes the modifiers for the transformation
** matrix for the initial image.
*/

void	fdf_initialize_modifier(t_mods *mods)
{
	mods->scale[0] = 10;
	mods->scale[1] = 10;
	mods->scale[2] = 10;
	mods->trans[0] = 0;
	mods->trans[1] = 0;
	mods->trans[2] = 0;
	mods->rotx = 0;
	mods->roty = 0;
	mods->rotz = 0;
	mods->focal = 200;
}

void	fdf_initialize_draw(char *file, t_canvas *c)
{
	EGUARD(get_data(file, c));
	c->mlx = mlx_init();
	EGUARD((c->img.id = mlx_new_image(c->mlx, c->s_x, c->s_y)));
	c->img.skt = mlx_get_data_addr
		(c->img.id, &c->img.bpp, &c->img.sl, &c->img.end);
	fdf_initialize_modifier(&c->mods);
	fdf_modify_coordinates(c);
	ft_printmap(&c->map);///

	EGUARD((c->win = mlx_new_window(c->mlx, c->s_x, c->s_y, "fdf")));
	mlx_put_image_to_window(c->mlx, c->win, c->img.id, 10, 0);
}
