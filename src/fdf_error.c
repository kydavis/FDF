/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:53:36 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/22 14:16:40 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

/*
** In case of error it prints the appropriate Error message
*/

void	fdf_perror(int en)
{
	if (en == -1)
		ft_dprintf(2, "ERRNO:%d No file found\n", en);
	else if (en == -2)
		ft_dprintf(2, "ERRNO:%d No Data found\n", en);
	else if (en == -3)
		ft_dprintf(2, "ERRNO:%d Found wrong line length\n", en);
	else if (en == -4)
		ft_dprintf(2, "ERROR:%d\n", en);
	else if (en == -5)
		ft_dprintf(2, "ERRNO:%d Size specifications are too large\n", en);
	else if (en == -6)
		ft_dprintf(2, "ERRNO:%d Pixel is outside of size specification\n", en);
	else if (en == -7)
		ft_dprintf(2, "ERRNO:%d Error closing map\n", en);
}

/*
** Cleanup function, destroys any outstanding images or windows. Then exits
** out of the program.
*/

void	fdf_cleanup(int en, t_canvas *c)
{
	if (c->img.id && c->mlx)
		mlx_destroy_image(c->mlx, c->img.id);
	if (c->win && c->mlx)
		mlx_destroy_window(c->mlx, c->win);
	ft_memdel((void*)&c->map.loc);
	ft_memdel((void*)&c->map.twd);
	ft_memdel((void*)&c->sintable);
	ft_memdel((void*)&c->costable);
	fdf_perror(en);
	exit(en);
}
