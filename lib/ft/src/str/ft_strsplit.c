/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 18:16:43 by kdavis            #+#    #+#             */
/*   Updated: 2016/10/05 10:06:29 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** Allocates and returns an array of strings (all null terminated, including
** the array itself) obtained by splitting string s by using character c as a
** delimiter.
*/

char	**ft_strsplit(char const *s, char c)
{
	char			**r;
	size_t			word_len;
	unsigned int	result_index;

	if (!s || !(r = (char**)malloc(8 * (ft_splcount(s, c, ft_strlen(s)) + 1))))
		return (NULL);
	result_index = 0;
	while (ft_splcount(s, c, ft_strlen(s)) > 0)
	{
		word_len = 0;
		while (*s == c)
			s++;
		while (s[word_len] != c && s[word_len])
			word_len++;
		if (!(r[result_index++] = ft_strsub(s, 0, word_len)))
		{
			while (result_index-- > 0)
				free((r[result_index]));
			free(r);
			return (NULL);
		}
		s += word_len;
	}
	r[result_index] = 0;
	return (r);
}
