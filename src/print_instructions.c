/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 14:47:10 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/17 19:15:51 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

static void	print_inst_cont(void)
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
}

void		print_instructions(void)
{
	print_inst_cont();
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
