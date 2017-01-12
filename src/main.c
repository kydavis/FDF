/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:45:47 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/11 15:43:00 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

/*
** more instructions
*/

static void	print_inst_cont(void)
{
	ft_putendl("'1':\tinvert x rotation");
	ft_putendl("'2':\tinvert y rotation");
	ft_putendl("'3':\tinvert z rotation");
	ft_putendl("'0':\tbirds eyes view (rotation on all axis are 0)");
	ft_putendl("spc:\tisometric view");
	ft_putendl("\n < :\tshift  image direction:left");
	ft_putendl(" > :\tshift  image direction:right");
	ft_putendl(" ^ :\tshift  image direction:up");
	ft_putendl(" v :\tshift  image direction:down");
	ft_putendl(" + :\tzoom in");
	ft_putendl(" - :\tzoom out");
	ft_putendl("lshift:\tcycle colors");
	ft_putendl("rshift:\tback cycle colors");
}

/*
** Cause I thought it looked cool
*/

static void	print_instructions(void)
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
	ft_putendl("'q':\trotate image direction:+1.4 degrees axis: x");
	ft_putendl("'e':\trotate image direction:-1.4 degrees axis: x");
	ft_putendl("'w':\trotate image direction:+1.4 degrees axis: y");
	ft_putendl("'s':\trotate image direction:-1.4 degrees axis: y");
	ft_putendl("'d':\trotate image direction:+1.4 degrees axis: z");
	ft_putendl("'a':\trotate image direction:-1.4 degrees axis: z");
	ft_putendl("'7':\trotate image direction:+90 degrees axis: x");
	ft_putendl("'9':\trotate image direction:-90 degrees axis: x");
	ft_putendl("'8':\trotate image direction:+90 degrees axis: y");
	ft_putendl("'5':\trotate image direction:-90 degrees axis: y");
	ft_putendl("'4':\trotate image direction:+90 degrees axis: z");
	ft_putendl("'6':\trotate image direction:-90 degrees axis: z");
	print_inst_cont();
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
	fdf_rotate(&can->model.obj, kc);
	if (kc == ESC)
		fdf_cleanup(0, can);
	if (kc == UA || kc == DA)
		can->model.shiftv += (kc == UA ? can->s_y / 20 : -can->s_y / 20);
	if (kc == LA || kc == RA)
		can->model.shifth += (kc == RA ? can->s_x / 20 : -can->s_x / 20);
	if (kc == RSHIFT || kc == LSHIFT)
		can->map.bcolor += (kc == LSHIFT ? 1 : -1) * 0x0F0F0F;
	if (kc == PS || kc == MS)
		fdf_zoom(can->model.obj.scale, kc, can->map.w, can->map.h);
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

int			main(int argc, char **argv)
{
	t_canvas	canv;

	if (argc == 2 || argc == 4)
	{
		ft_bzero((void *)&canv, sizeof(canv));
		if (!(canv.sintable = fdf_sin_cos_init(&canv.costable)))
			fdf_cleanup(-4, &canv);
		canv.s_x = (argc == 4 ? ft_atoi(argv[2]) : 0);
		canv.s_y = (argc == 4 ? ft_atoi(argv[3]) : 0);
		if (canv.s_x > 3600 || canv.s_y > 3600)
			fdf_cleanup(-5, &canv);
		fdf_initialize_draw(argv[1], &canv);
		print_instructions();
		mlx_key_hook(canv.win, hooks, (void *)&canv);
		mlx_loop(canv.mlx);
	}
	else
		ft_putendl("Usage: ./fdf <filename> [window width] [window length]");
	return (0);
}
