/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_initalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:05:48 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/22 17:20:09 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <fcntl.h>

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
** Draw outline:
**	open file
**	read file (but what will i read it into. )
**
*/
/*
static void		ft_printmap(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
			ft_printf("%3d ",map->nods[y][x++].z);
		ft_printf("\n");
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
	draw_line(c);
*/
	EGUARD((c->win = mlx_new_window(c->mlx, c->s_x, c->s_y, "fdf")));
	mlx_put_image_to_window(c->mlx, c->win, c->img.id, 0, 0);
}
