/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:45:47 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/08 15:01:27 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

/*
** Cause I thought it looked cool
*/

static void	print_instructions()
{
	ft_putendl("#############################################################");
	ft_putendl("##                                                         ##");
	ft_putendl("##           ##########     #####        ##########        ##");
	ft_putendl("##          ##             ##   ##      ##                 ##");
	ft_putendl("##         #########      ##    ##     #########           ##");
	ft_putendl("##        ##             ##   ##      ##                   ##");
	ft_putendl("##       ##             ######       ##                    ##");
	ft_putendl("##                                                         ##");
	ft_putendl("#############################################################");
	ft_putendl("\nInstructions");
	ft_putendl("esc:\tquit program");
	ft_putendl("'q':\trotate image direction:counterclockwise axis: x");
	ft_putendl("'e':\trotate image direction:clockwise        axis: x");
	ft_putendl("'w':\trotate image direction:counterclockwise axis: y");
	ft_putendl("'s':\trotate image direction:clockwise        axis: y");
	ft_putendl("'d':\trotate image direction:counterclockwise axis: z");
	ft_putendl("'a':\trotate image direction:clockwise        axis: z");
	ft_putendl("\n < :\tshift  image direction:left");
	ft_putendl(" > :\tshift  image direction:right");
	ft_putendl(" ^ :\tshift  image direction:up");
	ft_putendl(" v :\tshift  image direction:down");
}


/*
** Place holder, may evolve into image manipulator dispatcher
*/

static int	hooks(int kc, void *param)
{
	t_canvas	*can;
	int			i;	

	i = ~0;
	can = (t_canvas*)param;
	ft_printf("kc: %d char?:%c\n", kc, kc);
	if (kc == ESC)
		fdf_cleanup(0, can);
	if (kc == Q || kc == E || kc == W || kc == S || kc == D || kc == A || kc == N6
			|| kc == N5 || kc == N4 || kc == N7 || kc == N8 || kc == N9)
		fdf_rotate(&can->mods, kc);
/*	if (kc == W || kc == S)
		can->mods.roty += (kc == W ? 1 : -1);
	if (kc == D || kc == A)
		can->mods.rotz += (kc == A ? 1 : -1);*/
	if (kc == PS || kc == MS)
		fdf_zoom(can->mods.scale, kc);
	fdf_modify_coordinates(can);
	ft_bzero(can->img.skt, (can->s_x * can->s_y) * 4);
	fdf_draw_map(can);
	mlx_clear_window(can->mlx, can->win);
	mlx_put_image_to_window(can->mlx, can->win, can->img.id, 0, 0);
	return (0);
}

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
		if (!(canv.sintable = fdf_sin_cos_init(&canv.costable)))
			fdf_cleanup(-4, &canv);
		canv.s_x = (argc == 4 ? ft_atoi(argv[2]) : 1280);
		canv.s_y = (argc == 4 ? ft_atoi(argv[3]) : 720);
		if (canv.s_x > 3600 || canv.s_y > 3600)
			fdf_cleanup(-5, &canv);

		fdf_initialize_draw(argv[1], &canv);
		print_instructions();///
		mlx_key_hook(canv.win, hooks, (void *)&canv);
		mlx_loop(canv.mlx);
	}
	else
		ft_putendl("Usage: ./fdf <filename> [window width] [window length]");
	return (0);
}
