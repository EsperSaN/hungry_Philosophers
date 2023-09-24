/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:58:06 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/22 11:19:21 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	sleep_ms(size_t milisec)
{
	usleep(milisec * 1000);
}

long	mins_ab_value(long x, long y)
{
	long res;
	
	res = x - y;
	if (res < 0)
		return (res * -1);
	else
		return (res);
}

void	report(t_philo *p, char *report)
{
	long	time;
	long	local_time;
	long	ms_time; 
	
	pthread_mutex_lock(p->print);
	ms_time = get_time();
	local_time = ms_time - p->begin_time;
	printf("[%lu] - [%lu] = [%d]\n", ms_time, p->live_until , p->live_until - ms_time);
	printf("[%lu] philo [%lu] %s\n", local_time, p->no, report);
	pthread_mutex_unlock(p->print);
}

void	hungry_now(t_philo	*philo)
{
	long ms_time;

	report(philo, "is thingking");
	if (philo->no % 2 == 0)
	{
		pthread_mutex_lock(philo->spoon_right);
		pthread_mutex_lock(philo->spoon_left);
	}
	else
	{
		pthread_mutex_lock(philo->spoon_left);
		pthread_mutex_lock(philo->spoon_right);
	}
	report(philo, "is eating");
	sleep_ms(philo->eat_time);
	ms_time = get_time();
	philo->live_until = ms_time + philo->die_time;
	pthread_mutex_unlock(philo->spoon_left);
	pthread_mutex_unlock(philo->spoon_right);

}

void	*rout(void *av)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *) av;
	count = 1;
	philo->deploy_time = get_time();
	philo->live_until = philo->deploy_time + philo->die_time;
	printf("p [%lu]die_time [%lu]live until [%lu]\n", philo->no,philo->die_time, philo->live_until);
	while (count)
	{
		hungry_now(philo);
		count++;
		if (count == philo->eat_count)
		{
			printf("count?????\n");
			return(0);
		}
		//printf("sleep[%lu]from thinking\n", philo->think_time);
		report(philo, "is slipping");
		sleep_ms(philo->sleep_time);

	}
	return (0);
}
