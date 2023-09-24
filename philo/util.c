/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:49:02 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/17 10:05:14 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_num(char c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	is_all_num(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (!is_num(*str))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int				len;
	int				lob;
	unsigned long	result;

	len = 0;
	result = 0;
	lob = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'\
				|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			lob = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		len++;
	}
	return ((result * lob));
}
