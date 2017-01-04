/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_sinlookup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:32:02 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/03 14:37:05 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <math.h>

float	*fdf_sin_cos_init(float **cs)
{
	float	*sn;
	int		i;

	if (!(*cs = (float*)malloc(sizeof(float) * 256)))
		return (NULL);
	if (!(sn = (float*)malloc(sizeof(float) * 256)))
	{
		ft_memdel((void**)cs);
		return (NULL);
	}
	i = -1;
	while (++i < 256)
	{
		*(sn + i) = sin(i * M_PI / 128);
		*(*cs + i) = cos(i * M_PI / 128);
	}
	return (sn);
}
