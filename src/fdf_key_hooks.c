/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:46:22 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/17 19:14:35 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_zoom is a key hook that will adjust the scaling matrix to zoom in to
** or zoom out.
*/

void	fdf_zoom(float *scl, char *keys, int w, int h)
{
	float	maxzoom;
	int		i;

	i = 0;
	maxzoom = 1.0 / (w < h ? w : h);
	if (((*scl * 2) >= maxzoom && keys[PS]))
		return ;
	if (keys[PS])
		while (i < 3)
			scl[i++] *= 2;
	else
		while (i < 3)
			scl[i++] *= 0.5;
	keys[PS] = 0;
	keys[MS] = 0;
}

/*
** key hooks for moving the image
*/

void	fdf_translate(t_canvas *can)
{
	can->model.shiftv += can->keys[UA] * (can->s_y / 20);
	can->model.shiftv -= can->keys[DA] * (can->s_y / 20);
	can->model.shifth += can->keys[RA] * (can->s_x / 20);
	can->model.shifth -= can->keys[LA] * (can->s_x / 20);
}

/*
** Key_hooks responsible for inverting the x,y, or z rotation or for changing
** the map to a predefined position.
*/

void	fdf_setmap(t_mods *mods, char *keys)
{
	if (keys[N1])
		mods->rotx *= -1;
	if (keys[N2])
		mods->roty *= -1;
	if (keys[N3])
		mods->rotz *= -1;
	if (keys[SPACE] || keys[N0])
	{
		mods->rotx = (keys[SPACE] ? -85 : 0);
		mods->roty = (keys[SPACE] ? -85 : 0);
		mods->rotz = (keys[SPACE] ? -85 : 0);
		keys[SPACE] = 0;
		keys[N0] = 0;
	}
	keys[N1] = 0;
	keys[N2] = 0;
	keys[N3] = 0;
}

/*
** key hooks for rotating the objects rotation.
*/

void	fdf_rotate(t_mods *mods, char *keys)
{
	mods->rotz += keys[N4] * 64;
	mods->rotz -= keys[N6] * 64;
	mods->rotz += keys[A];
	mods->rotz -= keys[D];
	mods->roty += keys[N8] * 64;
	mods->roty -= keys[N5] * 64;
	mods->roty += keys[W];
	mods->roty -= keys[S];
	mods->rotx += keys[N7] * 64;
	mods->rotx -= keys[N9] * 64;
	mods->rotx += keys[Q];
	mods->rotx -= keys[E];
	fdf_setmap(mods, keys);
}
