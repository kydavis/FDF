/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:05:48 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/06 20:22:21 by kdavis           ###   ########.fr       */
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
** fdf_draw_map draws the map based on the current coordinate load
*/

int		fdf_draw_map(t_canvas *c)
{
	int	i;
	int	area;

	i = 0;
	area = c->map.w * c->map.h;
	while ((i + 1) < area)
	{
		if ((i + 1) % c->map.w != 0)
		{
			ft_printf("\nfrom:%d to %d\n", i, i + 1);
			fdf_draw_line(&c->map.twd[i], &c->map.twd[i + 1], c);
		}
		if ((i + c->map.w) / area == 0)
		{
			ft_printf("\nfrom:%d to %d\n", i, i + c->map.w);
			fdf_draw_line(&c->map.twd[i], &c->map.twd[i + c->map.w], c);
		}
		i++;
	}
	return (1);
}

/*
** fdf_initialize_modifier initializes the modifiers for the transformation
** matrix for the initial image.
*/

void	fdf_initialize_modifier(t_mods *mods)
{
	mods->scale[0] = 1;
	mods->scale[1] = 1;
	mods->scale[2] = 1;
	mods->trans[0] = 0;
	mods->trans[1] = 0;
	mods->trans[2] = 0;
	mods->rotx = 0;
	mods->roty = 0;
	mods->rotz = 0;
	mods->focal = 100;
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
	fdf_draw_map(c);

	EGUARD((c->win = mlx_new_window(c->mlx, c->s_x, c->s_y, "fdf")));
	mlx_put_image_to_window(c->mlx, c->win, c->img.id, 10, 0);
}
