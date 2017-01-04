/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mx_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:48:55 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/03 15:33:45 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_mx_rotx creates a rotation matrix for rotating the image around the x
** axis by a degrees. (degrees are in terms of 256 degrees for a full circle)
**
** rotation matrix:
**	1	0	0	0
**	0	C	S	0
**	0	-S	C	0
**	0	0	0	1
*/

float	*fdf_mx_rotx(int a, t_canvas *c)
{
	float	*rot;

	if (!(rot = mx_id(4)))
		return (NULL);
	rot[5] = COS(a);
	rot[6] = SIN(a);
	rot[9] = -rot[6];
	rot[10] = rot[5];
	return (rot);
}

/*
** fdf_mx_roty creates a rotation matrix for rotating the image around the y
** axis by a degrees. (degrees are in terms of 256 degrees for a full circle)
**
** rotation matrix:
**	C	0	-S	0
**	0	1	0	0
**	S	0	C	0
**	0	0	0	1
*/

float	*fdf_mx_roty(int a, t_canvas *c)
{
	float	*rot;

	if (!(rot = mx_id(4)))
		return (NULL);
	rot[0] = COS(a);
	rot[8] = SIN(a);
	rot[2] = -rot[8];
	rot[10] = rot[0];
	return (rot);
}

/*
** fdf_mx_rotz creates a rotation matrix for rotating the image around the z
** axis by a degrees. (degrees are in terms of 256 degrees for a full circle)
**
** rotation matrix:
**	C	S	0	0
**	-S	C	0	0
**	0	0	1	0
**	0	0	0	1
*/

float	*fdf_mx_rotz(int a, t_canvas *c)
{
	float	*rot;

	if (!(rot = mx_id(4)))
		return (NULL);
	rot[0] = COS(a);
	rot[1] = SIN(a);
	rot[4] = -rot[1];
	rot[5] = rot[0];
	return (rot);
}
