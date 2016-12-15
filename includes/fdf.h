/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 06:45:34 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/14 12:25:47 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** General plan:
**	main:
** 		Initialize window.
**		have usage printing.
**		Write instructions to terminal.
**		call the fdf_loop.

**	fdf loop:
**		has the hooks and the different functions for each hook.
**		hooks:
**			'wasd' keys will rotate the image in the corresponding direction.
**			'lrud' arrow keys will shift the location of origin on the window.
**			'+-' to zoom in and out by a factor of 10.
**			(bonus: have keys that shift the color spectrum)
**			(bonus: shift view type based on key press)
**			(bonus: mouse hook to drag image)
**			<esc> hook to exit program.
**			(expose hook???)
**			loop_hook (clear image, just keep redrawing?)
**
**
**	draw image:
**		initalize image.
**		draw to image.
**		put image to screen.
**		destroy image.
**		||
**		if (!(image))
**			initalize image && draw image.
**		else
**			modify image.
**			place image.
**
**	initalize and draw image:
**		initalize image:
**		read and create

**	Error:
**		have a garbage collection function that frees everything and closes out.
**
**	List of Errors:
**		No file found (when open == -1)
**		No Data found (First line is empty)
**		Found wrong line length (not an equal number of "numbers" per line)
*/

#ifndef FDF_H
# define FDF_H

typedef struct	s_canvas
{
	void		*mlx;
	void		*win;
	void		*img;
}				t_canvas;

typedef struct	s_vector
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_vector;

#endif
