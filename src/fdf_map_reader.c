/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 13:26:54 by kdavis            #+#    #+#             */
/*   Updated: 2017/01/04 17:02:08 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>

static int		get_value(char **str, int *nbr, float *fl)
{
	long long	temp;
	int			ern;

	if ((ern = ft_getll_base(str, &temp)) < 1)
		return (ern);
	if (nbr)
		*nbr = (int)temp;
	if (fl)
		*fl = (float)temp;
	return (1);
}

static int		fill_row(int w, int lnbr, t_node *row, char *line)
{
	int		i;
	int		ern;

	i = -1;
	while (++i < w)
	{
		(row + i)->x = i - (w / 2);
		(row + i)->y = lnbr;;
		if ((ern = get_value(&line, NULL, &(row + i)->z)) < 1)
			return (ern);
		if (*line == ',')
		{
			line++;
			if ((ern = get_value(&line, &(row + i)->color, NULL)) < 1)
				return (ern);
		}
		else
			(row + i)->color = (row + i)->z;
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
	int		ln;

	i = 0;
	area = w * h;
	if (!(map = (t_node *)ft_memalloc(sizeof(t_node) * area)))
		return (NULL);
	while (i < area)
	{
		ln = (i / w) - (h / 2);
		if ((get_next_line(fd, &line)) <= 0 || 
				(fill_row(w, ln, (map + i), line)) < 1)
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
	if (!(c->map.nods = fill_map(fd, c->map.h, c->map.w)))
		fdf_cleanup(-4, c);
	if ((close(fd)) == -1)
		fdf_cleanup(-7, c);
	return (1);
}
