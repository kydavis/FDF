/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 12:40:24 by kdavis            #+#    #+#             */
/*   Updated: 2016/09/29 07:32:19 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*
** Creates a new string that concatenates s1 and s2.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;

	if (!s1 || !s2)
		return (NULL);
	if (!(sub = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	sub = ft_strcpy(sub, s1);
	sub = ft_strcat(sub, s2);
	return (sub);
}
