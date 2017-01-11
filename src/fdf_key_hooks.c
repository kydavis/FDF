/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:46:22 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/11 13:57:17 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_zoom is a key hook that will adjust the scaling matrix to zoom in to
** or zoom out.
*/

void	fdf_zoom(float *scl, int keycode, int w, int h)
{
	float	maxzoom;
	int		i;

	i = 0;
	maxzoom = 1.0 / (w < h ? w : h);
	if (((*scl * 2) >= maxzoom && keycode == PS))
		return ;
	while (i < 3)
		scl[i++] *= (keycode == PS ? 2 : 0.5);
	ft_printf("Zoom X%d\n", (int)(maxzoom / *scl));
}

/*
** Key_hooks responsible for inverting the x,y, or z rotation or for changing
** the map to a predefined position.
*/

void	fdf_setmap(t_mods *mods, int keycode)
{
	if (keycode == N1)
		mods->rotx *= -1;
	if (keycode == N2)
		mods->roty *= -1;
	if (keycode == N3)
		mods->rotz *= -1;
	if (keycode == SPACE || keycode == N0)
	{
		mods->rotx = (keycode == SPACE ? -85 : 0);
		mods->roty = (keycode == SPACE ? -85 : 0);
		mods->rotz = (keycode == SPACE ? -85 : 0);
	}
}

/*
** key hooks for rotating the objects rotation.
*/

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
	fdf_setmap(mods, keycode);
	ft_printf("x rotation:%d°, y rotation:%d°, z rotation:%d°\n",
			(int)(((float)mods->rotx / 256) * 360) % 360,
			(int)(((float)mods->roty / 256) * 360) % 360,
			(int)(((float)mods->rotz / 256) * 360) % 360);
}

/*
** key hooks for modifying the color of the object
*/

