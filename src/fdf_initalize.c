/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:05:48 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/11 15:54:46 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>

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
			fdf_draw_line(c->map.twd[i], c->map.twd[i + 1], c);
		if ((i + c->map.w) / area == 0)
			fdf_draw_line(c->map.twd[i], c->map.twd[i + c->map.w], c);
		i++;
	}
	return (1);
}

/*
** fdf_initialize_modifier initializes the modifiers for the transformation
** matrix for the initial image.
*/

void	fdf_initialize_modifier(t_canvas *c)
{
	c->model.obj.scale[0] = .02 / (c->map.w > c->map.h ? c->map.w : c->map.h);
	c->model.obj.scale[1] = .02 / (c->map.w > c->map.h ? c->map.w : c->map.h);
	c->model.obj.scale[2] = .02 / (c->map.w > c->map.h ? c->map.w : c->map.h);
	c->model.obj.trans[0] = 0;
	c->model.obj.trans[1] = 0;
	c->model.obj.trans[2] = 0;
	c->model.obj.rotx = -85;
	c->model.obj.roty = -85;
	c->model.obj.rotz = -85;
	c->model.focal = 48000;
	c->model.shifth = 0;
	c->model.shiftv = 0;
}

void	fdf_initialize_draw(char *file, t_canvas *c)
{
	int	winscale;

	EGUARD(get_data(file, c));
	winscale = (c->s_x > 100 ? 5 : 50);
	c->s_x = (c->s_x ? c->s_x : c->map.w * winscale);
	winscale = (c->s_y > 100 ? 5 : 50);
	c->s_y = (c->s_y ? c->s_y : c->map.h * winscale);
	c->s_y = (c->s_y < 1764 ? c->s_y : 1764);
	c->s_x = (c->s_x < 3200 ? c->s_x : 3200);
	fdf_initialize_modifier(c);
	c->mlx = mlx_init();
	EGUARD((c->img.id = mlx_new_image(c->mlx, c->s_x, c->s_y)));
	c->img.skt = mlx_get_data_addr(c->img.id,
			&c->img.bpp, &c->img.sl, &c->img.end);
	fdf_modify_coordinates(c);
	fdf_draw_map(c);
	EGUARD((c->win = mlx_new_window(c->mlx, c->s_x, c->s_y, "fdf")));
	mlx_put_image_to_window(c->mlx, c->win, c->img.id, 0, 0);
}
