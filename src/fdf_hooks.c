/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 15:48:14 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/17 19:10:29 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

/*
** Turn on key when pressed
*/

int	kp_hooks(int kc, void *param)
{
	if (kc < 264 && kc >= 0)
		((t_canvas*)param)->keys[kc] = 1;
	return (0);
}

/*
** Turn off keys when released
*/

int	kr_hooks(int kc, void *param)
{
	if (kc < 264 && kc >= 0)
		((t_canvas*)param)->keys[kc] = 0;
	return (0);
}

int	exit_hook(void *param)
{
	fdf_cleanup(0, (t_canvas*)param);
	return (0);
}
