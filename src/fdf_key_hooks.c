/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:46:22 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/08 15:07:37 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_zoom is a key hook that will adjust the scaling matrix to zoom in to
** or zoom out.
*/

void	fdf_zoom(float *scl, int keycode)
{
	int	i;

	i = 0;
	if ((*scl >= 1 && keycode == PS) || (*scl < (0.25 / 8) && keycode == MS))
		return ;
	while (i < 3)
	{
		scl[i++] *= (keycode == PS ? 2 : 0.5);
	}
}

void	fdf_rotate(t_mods *mods, int keycode)
{
	if (keycode == N6 || keycode == N4 || keycode == A || keycode == D)
	{
		if (keycode == N6 || keycode == N4)
			mods->rotz += (keycode == N4 ? 64 : -64);
		else
			mods->rotz += (keycode == A ? 1 : -1);
	}
	if (keycode == N5 || keycode == N8 || keycode == W || keycode == S)
	{
		if (keycode == N8 || keycode == N5)
			mods->roty += (keycode == N8 ? 64 : -64);
		else
			mods->roty += (keycode == W ? 1 : -1);
	}
	if (keycode == N7 || keycode == N9 || keycode == Q || keycode == E)
	{
		if (keycode == N7 || keycode == N9)
			mods->rotx += (keycode == N7 ? 64 : -64);
		else
			mods->rotx += (keycode == Q ? 1 : -1);
	}
	ft_printf("x rotation:%d°, y rotation:%d°, z rotation:%d°\n", (int)(((float)mods->rotx / 256) * 360),
			(int)(((float)mods->roty / 256) * 360),(int)(((float)mods->rotz / 256) * 360));
}
