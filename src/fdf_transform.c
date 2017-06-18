/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 12:40:29 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/17 19:06:43 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** fdf_mod_matrix creates the matrix used for modifying the 3d coordinates.
** flag == 0: modifier matrix for local->world
** flag != 0: modifier matrix for world->aligned.
*/

static void	fdf_mod_matrix(t_canvas *c, char flag)
{
	fdf_mx_id(c->model.obj.mmat);
	if (!(flag))
	{
		fdf_mx_scale_tr(c->model.obj.scale, 3, c->model.obj.mmat, 1);
		fdf_mx_rot(c, &c->model.obj);
		fdf_mx_scale_tr(c->model.obj.trans, 3, c->model.obj.mmat, 0);
	}
}

/*
** fdf_modify_coordinates will fill in the aligned node array with the
** transformed 3d coordinates for each node.
*/

int			fdf_modify_coordinates(t_canvas *c)
{
	int	i;
	int	area;

	i = -1;
	area = c->map.h * c->map.w;
	fdf_mod_matrix(c, 0);
	while (++i < area)
		fdf_vec_tranf((c->map.loc + i), c, (c->map.twd + i), i);
	return (1);
}
