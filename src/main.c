/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:45:47 by kdavis            #+#    #+#             */
/*   Updated: 2016/12/14 18:23:10 by kdavis           ###   ########.fr       */
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
	t_canvas	canv;

	if (argc == 2 || argc == 4)
	{
		ft_bzero((void *)&canv, sizeof(canv));
		canv.mlx = mlx_init();
		canv.s_x = (argc == 4 ? ft_atoi(argv[2]) : 100);
		canv.s_y = (argc == 4 ? ft_atoi(argv[3]) : 100);
		canv.win =  mlx_new_window(canv.mlx, canv.s_x, canv.s_y, "fdf");
	}
	else
		ft_putendl("Usage: ./fdf <filename>");
	(void)argv[1];
	return (0);
}
