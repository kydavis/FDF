/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:53:36 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/22 17:32:02 by kdavis           ###   ########.fr       */
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
		ft_dprintf(2, "ERRNO:%d Memory allocation failure\n", en);
	else if (en == -5)
		ft_dprintf(2, "ERRNO:%d Size specifications are too large\n", en);
	else if (en == -6)
		ft_dprintf(2, "ERRNO:%d Pixel is outside of size specification\n", en);
	else if (en == -7)
		ft_dprintf(2, "ERRNO:%d Error closing map\n", en);
	else///
		ft_dprintf(2, "ERRNO:%d No errors just closing\n", en);///
}

/*
** Cleanup function, destroys any outstanding images or windows. Then exits
** out of the program.
*/

void	fdf_cleanup(int en, t_canvas *c)
{
/*	ft_printf("fdf cleanup\n");*/
	if (c->img.id && c->mlx)
		mlx_destroy_image(c->mlx, c->img.id);
	if (c->win && c->mlx)
		mlx_destroy_window(c->mlx, c->win);
	ft_delgrid((void***)&c->map.nods);
	fdf_perror(en);
	exit(en);
}

/*
** fdf_freer is a cleanup function that frees allocations made in a function
** before returning the ern to the parent function.
*/

int		fdf_freer(int ern, void **str, void ***grid)
{
	ft_memdel(str);
	ft_delgrid(grid);
	return (ern);
}
