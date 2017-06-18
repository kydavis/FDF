/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:45:47 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/17 19:14:18 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

static void	redraw_map(t_canvas *can)
{
	fdf_rotate(&can->model.obj, can->keys);
	fdf_translate(can);
	if (can->keys[ESC])
		fdf_cleanup(0, can);
	if (can->keys[RSHIFT] || can->keys[LSHIFT])
	{
		can->map.bcolor += can->keys[LSHIFT] * 0x0F0F0F;
		can->map.bcolor -= can->keys[RSHIFT] * 0x0F0F0F;
		can->keys[RSHIFT] = 0;
		can->keys[LSHIFT] = 0;
	}
	if (can->keys[PS] || can->keys[MS])
		fdf_zoom(can->model.obj.scale, can->keys, can->map.w, can->map.h);
	fdf_modify_coordinates(can);
	ft_bzero(can->img.skt, (can->s_x * can->s_y) * 4);
	fdf_draw_map(can);
	mlx_clear_window(can->mlx, can->win);
	mlx_put_image_to_window(can->mlx, can->win, can->img.id, 0, 0);
}

static int	refresh(void *param)
{
	t_canvas	*canvas;
	uint64_t	*checker;
	int			i;
	uint64_t	redraw;

	canvas = (t_canvas*)param;
	checker = (uint64_t*)canvas->keys;
	i = 0;
	redraw = 0;
	while (i < 33)
	{
		redraw = redraw | checker[i];
		i++;
	}
	if (redraw)
		redraw_map(canvas);
	return (0);
}

/*
** Hook dispatacher
** TODO:
**	mlx_hook(canvas->win, 4, 0, mouse_press, (void *)&canvas);
**	mlx_hook(canvas->win, 5, 0, mouse_release, (void *)&canvas);
**	mlx_hook(canvas->win, 6, 0, mouse_drag_hook, (void *)&canvas);
*/

static void	fdf_hooks(t_canvas *canvas)
{
	mlx_hook(canvas->win, 2, 0, kp_hooks, (void *)canvas);
	mlx_hook(canvas->win, 3, 0, kr_hooks, (void *)canvas);
	mlx_hook(canvas->win, 17, 0, exit_hook, (void *)canvas);
	mlx_loop_hook(canvas->mlx, refresh, (void *)canvas);
	mlx_loop(canvas->mlx);
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
		fdf_hooks(&canv);
	}
	else
		ft_putendl("Usage: ./fdf <filename> [window width] [window length]");
	return (0);
}
