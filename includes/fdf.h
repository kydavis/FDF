/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 06:45:34 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/05 19:20:44 by kdavis           ###   ########.fr       */
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

**	Drawing outline:
**		Calculate center of the window (this point will act as an origin)
**		Calculate y and x values of the coordinates as they relate to the origin
**		Do matrix shit

**	Error:
**		have a garbage collection function that frees everything and closes out.
**
**	List of Errors:
**		No file found (when open == -1)
**		No Data found (First line is empty)
**		Found wrong line length (not an equal number of "numbers" per line)
*/

/*
** Keycodes:
** ESC = 53
** Q = 12
** E = 14
** W = 13
** S = 1
** D = 2
** A = 0
** LA = 123
** RA = 124
** UA = 126
** DA = 125
*/

#ifndef FDF_H
# define FDF_H

/*
** Library included for use of the uint32_t typedef
*/
# include <stdint.h>
# include <math.h>

# define ESC  53
# define Q  12
# define E  14
# define W  13
# define S  1
# define D  2
# define A  0
# define LA 123
# define RA  124
# define UA  126
# define DA  125

# define EGUARD(X) ((X) ? 0 : fdf_cleanup(-4, c))
# define SIN(X) c->sintable[ft_absolute((int)X&255)]
# define COS(X) c->costable[ft_absolute((int)X&255)]

typedef struct s_modifier
{
	float		mmat[16];
	float		scale[3];
	float		trans[3];
	int			rotx;
	int			roty;
	int			rotz;
	int			focal;
}				t_mods;

typedef struct	s_pix
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

typedef struct	s_node
{
	int			z;
	int			color;
}				t_node;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vect;

typedef struct	s_map
{
	t_node		*loc;
	t_pixel		*twd;
	int			h;
	int			w;
}				t_map;

typedef struct s_image
{
	void		*id;
	char		*skt;
	int			bpp;
	int			sl;
	int			end;
	int			ctr;
}				t_image;

typedef struct	s_canvas
{
	void		*mlx;
	void		*win;
	float		*sintable;
	float		*costable;
	t_mods		mods;
	t_image		img;
	t_map		map;
	int			s_x;
	int			s_y;
}				t_canvas;

/*
** fdf_sinlookup.c
*/
float	*fdf_sin_cos_init(float **cs);

/*
** fdf_matrix.c
*/
void			fdf_mx_rot(int ax, int ay, int az, t_canvas *c);
void			fdf_mx_scale_tr(float *fa, int len, float *ret, char flag);
void			fdf_vec_tranf(t_node *vec, t_canvas *c, t_pixel *twd, int ind);
void			fdf_mx_id(float *mat);

/*
** fdf_transform.c
*/
int			fdf_modify_coordinates(t_canvas *c);

/*
** fdf_error:
*/
void	fdf_cleanup(int en, t_canvas *c);
int		fdf_freer(int ern, void **str);

/*
** fdf_initalize
*/
void	fdf_initialize_draw(char *file, t_canvas *canv);

/*
** fdf_pixel.c
*/
int		pixel_to_img(t_canvas *c, t_pixel *p);

/*
** map_reader.c
*/
int			get_data(char *file, t_canvas *c);

#endif
