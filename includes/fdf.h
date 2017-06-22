/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 06:45:34 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/22 13:52:56 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** Library included for use of the uint32_t typedef
*/
# include <math.h>
# include <limits.h>

# define ESC  53
# define Q  12
# define E  14
# define W  13
# define S  1
# define D  2
# define A  0
# define LA 123
# define RA 124
# define UA 126
# define DA 125
# define PS	69
# define MS 78
# define N1 83
# define N2 84
# define N3 85
# define N6 88
# define N4 86
# define N5 87
# define N7 89
# define N9 92
# define N8 91
# define N0 82
# define SPACE 49
# define RSHIFT 258
# define LSHIFT 257

# define SIN(X) c->sintable[ft_absolute((int)X&255)]
# define COS(X) c->costable[ft_absolute((int)X&255)]

typedef struct	s_modifier
{
	float		mmat[16];
	float		scale[3];
	float		trans[3];
	int			rotx;
	int			roty;
	int			rotz;
}				t_mods;

typedef struct	s_model
{
	t_mods		obj;
	int			shifth;
	int			shiftv;
	int			focal;
}				t_model;

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

typedef struct	s_line
{
	t_pixel		*start;
	t_pixel		*end;
	long		dx;
	long		dy;
	int			octant;
}				t_line;

typedef struct	s_map
{
	t_node		*loc;
	t_pixel		*twd;
	int			h;
	int			w;
	int			bcolor;
	char		cf;
}				t_map;

typedef struct	s_image
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
	t_model		model;
	t_image		img;
	t_map		map;
	char		keys[264];
	int			s_x;
	int			s_y;
}				t_canvas;

void			ft_swap(int *a, int *b);

/*
** fdf_sinlookup.c
*/
float			*fdf_sin_cos_init(float **cs);

/*
** fdf_matrix.c
*/
void			fdf_mx_rot(t_canvas *c, t_mods *mod);
void			fdf_mx_scale_tr(float *fa, int len, float *ret, char flag);
void			fdf_vec_tranf(t_node *vec, t_canvas *c, t_pixel *twd, int ind);
void			fdf_mx_id(float *mat);

/*
** fdf_transform.c
*/
int				fdf_modify_coordinates(t_canvas *c);

/*
** fdf_error:
*/
void			fdf_cleanup(int en, t_canvas *c);
int				fdf_freer(int ern, void **str);

/*
** fdf_initalize
*/
int				fdf_draw_map(t_canvas *c);
void			fdf_initialize_draw(char *file, t_canvas *canv);

/*
** fdf_pixel.c
*/
int				pixel_to_img(t_canvas *c, t_pixel *p);

/*
** map_reader.c
*/
int				get_data(char *file, t_canvas *c);

/*
** fdf_draw_line.c
*/
void			fdf_draw_line(t_pixel p1, t_pixel p2, t_canvas *c);

/*
** fdf_line_clipping.c
*/
int				fdf_clip_coordinates(t_canvas *c, t_line *lin);

/*
** fdf_key_hooks.c
*/
void			fdf_zoom(float *scl, char *keys, int w, int h);
void			fdf_rotate(t_mods *mods, char *keys);
void			fdf_translate(t_canvas *can);

/*
** print_instructions.c
*/
void			print_instructions(void);

/*
** fdf_hooks.c
*/

int				kp_hooks(int kc, void *param);
int				kr_hooks(int kc, void *param);
int				exit_hook(void *param);

#endif
