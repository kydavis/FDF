/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:45:47 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/14 16:32:24 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

/*
** Main tasks:
**	-Create and initalize canvas struct.
**	-Connect to the server.
**	-Initialize window
*/

int	main(int argc, char **argv)
{
	t_canvas	canvas;

	if (argc != 2)
		ft_putendl("Usage: ./fdf <filename>");
	else
	{
		ft_bzero((void *)&canvas, sizeof(canvas));
/*		canvas.mlx = */
	}
	(void)argv[1];
	return (0);
}
