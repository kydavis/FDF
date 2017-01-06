/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mx_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:48:55 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/05 16:02:40 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_mxsquare_mult multiplies two dim X dim matrices m1, m2, and ret must all
** be arrays of size (dim ^ 2)
*/

static void	fdf_mxsquare_mult(float *m1, float *m2, float *ret, int dim)
{
	int		i;
	int		j;
	int		var;

	i = -1;
	while (++i < dim)
	{
		j = -1;
		while (++j < dim)
		{
			var = -1;
			while (++var < dim)
				ret[(i * dim) + j] += m1[i * dim + var] * m2[var * dim + j];
		}
	}
}

/*
** fdf_vector_mult creates the vector ret by retreiving the local coordinates
** of the node from the value stored at vec as well as the index of the value.
*/

void		fdf_vector_mult(t_node *vec, t_canvas *c, t_vect *ret, int ind)
{
	float	x;
	float	y;
	float	z;
	int		map_size;

	map_size = c->map.h * c->map.w;
	x = ind % map_size - (c->map.w / 2);
	y = ind / map_size - (c->map.h / 2);
	z = vec->z;
	ret->x = x * c->mods.mmat[0] + y * c->mods.mmat[4] +
				z * c->mods.mmat[8] + 1 * c->mods.mmat[12];
	ret->y = x * c->mods.mmat[1] + y * c->mods.mmat[5] +
				z * c->mods.mmat[9] + 1 * c->mods.mmat[13];
	ret->z = x * c->mods.mmat[2] + y * c->mods.mmat[6] +
				z * c->mods.mmat[10] + 1 * c->mods.mmat[14];
}

/*
** fdf_mx_id fills a float[16] array with a 4x4 identiy matrix.
**
** identity matrix:
**	1	0	0	0
**	0	1	0	0
**	0	0	1	0
**	0	0	0	1
*/

void		fdf_mx_id(float *mat)
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
** fdf_mx_scale_tr will either scale or translate the matrix ret by the
** values in the float array.
** flag == 0: translate matrix && modifier == the index of the final row.
** flag != 0: scale matrix && modifier == value diag index is divisible by.
*/

void		fdf_mx_scale_tr(float *fa, int len, float *ret, char flag)
{
	float	modm[16];
	float	temp[16];
	int		modifier;
	int		i;

	fdf_mx_id(modm);
	modifier = (flag ? len + 2 : len * (len + 1));
	i = -1;
	if (flag)
		while (++i < len)
			modm[modifier * i] = fa[i];
	else
		while (++i < len)
			modm[modifier + i] = fa[i];
	fdf_mxsquare_mult(ret, modm, temp, 4);
	i = -1;
	while (++i < 16)
		ret[i] = temp[i];
}

/*
** fdf_mx_rot creates a rotation matrix for rotating the image around the the
** different axises by the perspective degrees.
** (degrees are in terms of 256 degrees for a full circle)
** It does this by creating rotation matrices for each axis, and multiplying the
** matrix by these matrices.
**
** ret must be a 4x4 matrix for this function to work.
** (in other words a float[16])
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

void		fdf_mx_rot(int ax, int ay, int az, t_canvas *c)
{
	float	rotx[16];
	float	roty[16];
	float	rotz[16];
	float	temp1[16];
	float	temp2[16];

	fdf_mx_id(rotx);
	rotx[5] = COS(ax);
	rotx[6] = SIN(ax);
	rotx[9] = -rotx[6];
	rotx[10] = rotx[5];
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
	fdf_mxsquare_mult(c->mods.mmat, roty, temp1, 4);
	fdf_mxsquare_mult(temp1, rotx, temp2, 4);
	fdf_mxsquare_mult(temp2, rotz, c->mods.mmat, 4);
}
