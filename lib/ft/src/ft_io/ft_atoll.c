/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 13:13:46 by kdavis            #+#    #+#             */
/*   Updated: 2017/06/12 18:25:45 by kdavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include <limits.h>

/*
**  Converts a string of numbers into a long long.
*/

long long	ft_atoll(const char *str)
{
	unsigned long long	result;
	long long			neg;

	neg = 1;
	result = 0;
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str - 0))
	{
		result = 10 * result + ((*str++ - '0') % 10);
		if (result > LLONG_MAX)
			return (neg == 1 ? LLONG_MAX : LLONG_MIN);
	}
	return ((long long)(neg * result));
}
