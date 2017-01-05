/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mx_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:48:55 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/04 16:45:44 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_mx_id fills a float[16] array with a 4x4 identiy matrix.
**
** identity matrix:
**	1	0	0	0
**	0	1	0	0
**	0	0	1	0
**	0	0	0	1
*/

void	fdf_mx_id(float *mat)
{
	mat[0] = 1;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 0;
	mat[4] = 0;
	mat[5] = 1;
	mat[6] = 0;
	mat[7] = 0;
	mat[8] = 0;
	mat[9] = 0;
	mat[10] = 1;
	mat[11] = 0;
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1;
}

/*
** fdf_mx_rot creates a rotation matrix for rotating the image around the the
** different axises by the perspective degrees.
** (degrees are in terms of 256 degrees for a full circle)
** It does this by creating rotation matrices for each axis, and multiplying the
** matrix by these matrices.
**
** rotation matrix x:
**	1	0	0	0
**	0	C	S	0
**	0	-S	C	0
**	0	0	0	1
**
** rotation matrix y:
**	C	0	-S	0
**	0	1	0	0
**	S	0	C	0
**	0	0	0	1
**
** rotation matrix z:
**	C	S	0	0
**	-S	C	0	0
**	0	0	1	0
**	0	0	0	1
*/

void	fdf_mx_rot(int ax, int ay, int az, t_canvas *c)
{
	float	rotx[16];
	float	roty[16];
	float	rotz[16];
	float	temp1[16];
	float	temp2[16];

	fdf_mx_id(rotx);
	rotx[5] = COS(ax);
	rotx[6] = SIN(ax);
	rotx[9] = -rot[6];
	rotx[10] = rot[5];
	fdf_mx_id(roty);
	roty[0] = COS(ay);
	roty[8] = SIN(ay);
	roty[2] = -roty[8];
	roty[10] = roty[0];
	fdf_mx_id(rotz);
	rotz[0] = COS(az);
	rotz[1] = SIN(az);
	rotz[4] = -rotz[1];
	rotz[5] = rotz[0];
	c->gm * rotx = temp1;
	temp1 * roty = temp2;
	temp2 * rotz = c->gm;
}

