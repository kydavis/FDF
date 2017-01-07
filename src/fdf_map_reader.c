/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 13:26:54 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/06 19:34:28 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>

static int		get_value(char **str, int *nbr)
{
	long long	temp;
	int			ern;

	if ((ern = ft_getll_base(str, &temp)) < 1)
		return (ern);
	if (nbr)
		*nbr = (int)temp;
	return (1);
}

static int		fill_row(int w, t_node *row, char *line)
{
	int		i;
	int		ern;

	i = -1;
	while (++i < w)
	{
		if ((ern = get_value(&line, &(row + i)->z)) < 1)
			return (ern);
		if (*line == ',')
		{
			line++;
			if ((ern = get_value(&line, &(row + i)->color)) < 1)
				return (ern);
		}
		else
			(row + i)->color = 0xfffafa;
		while (!(ft_iswhitespace(*line)) && *line)
			line += 1;
	}
	return (ern);
}

/*
** fill_map is responsible for filling a double star node array with the
** elevation and color of each node. (if no color is specified in the map
** then the color will be specified based on the height of the node.)
*/

static t_node	*fill_map(int fd, int h, int w)
{
	t_node	*map;
	char	*line;
	int		area;
	int		i;

	i = 0;
	area = h * w;
	if (!(map = (t_node *)ft_memalloc(sizeof(t_node) * area)))
		return (NULL);
	while (i < area)
	{
		if ((get_next_line(fd, &line)) <= 0 ||
				(fill_row(w, (map + i), line)) < 1)
		{
			ft_memdel((void*)&map);
			ft_memdel((void*)&line);
			return (NULL);
		}
		ft_memdel((void*)&line);
		i += w;
	}
	return (map);
}

/*
** get_map_dimensions calculates the height and width of the map
** it also ensure that every row has an equal number of points.
*/

static int		get_map_dimensions(char *file, int *h, int *w)
{
	int		tempw;
	int		ern;
	int		fd;
	char	*row;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	while ((ern = get_next_line(fd, &row)) > 0)
	{
		tempw = ft_strfcount(row, &ft_iswhitespace);
		if (*h == 0)
			*w = tempw;
		if (tempw != *w)
			return (-3);
		(*h)++;
		free(row);
	}
	if ((close(fd)) == -1)
		return (-7);
	return (ern);
}

int				get_data(char *file, t_canvas *c)
{
	int		fd;
	int		ern;

	if ((ern = get_map_dimensions(file, &c->map.h, &c->map.w)) < 0)
		fdf_cleanup(ern, c);
	if ((fd = open(file, O_RDONLY)) == -1)
		fdf_cleanup(-1, c);
	if (!(c->map.loc = fill_map(fd, c->map.h, c->map.w)))
		fdf_cleanup(-4, c);
	if (!(c->map.twd = (t_pixel*)ft_memalloc(sizeof(t_pixel) * c->map.h * c->map.w)))
		fdf_cleanup(-4, c);
	if ((close(fd)) == -1)
		fdf_cleanup(-7, c);
	c->img.ctr = (c->s_x / 2) + (c->img.sl / 4) * c->s_y / 2;
	return (1);
}
