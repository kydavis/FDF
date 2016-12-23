/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 10:34:38 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/19 14:46:47 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fdf.h>
#include <mlx.h>

int	pixel_to_img(t_canvas *c, t_pixel *p)
{
	int	*pix;

	if (p->x >= c->s_x || p->y >= c->s_y || p->x < 0 || p->y < 0)
		return (0);
	pix = (int *)(c->img.skt + (c->img.bpp / 8 * p->x) + (c->img.sl * p->y));
	*pix = p->color;
	return (1);
}
