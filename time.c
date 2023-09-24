/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:13:43 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/24 21:08:39 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	mins_ab_value(long x, long y)
{
	long	res;

	res = x - y;
	if (res < 0)
		return (res * -1);
	else
		return (res);
}

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	dif_time(long time)
{
	return (get_time() - time);
}

void	sleep_ms(t_philo *p, size_t ms)
{
	long	ms_time_now;
	long	dif;

	p->p_time = get_time();
	dif = 0;
	if (p->is_die == 1)
		return ;
	while (dif < ms)
	{
		if (dif_time(p->last_eat_time) > p->die_time)
		{
			if (pthread_mutex_lock(p->print_lock))
				return ;
			printf("[%lu] philo [%d] die\n", dif_time(p->begin_time), p->no);
			p->is_die = 1;
		}
		dif = dif_time(p->p_time);
		usleep(10);
	}
}
