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
#define brake break


long	mins_ab_value(long x, long y)
{
	long res;
	
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
	long ms_time_now;
	long dif;

	p->p_time = get_time();
	dif = 0;
	while (dif < ms)
	{
		if (dif_time(p->last_eat_time) > p->die_time)
			exit (printf("[%lu] philo [%d] die\n", dif_time(p->begin_time), p->no));
		dif = dif_time(p->p_time);
		usleep(2);
	}
}

void	report(t_philo *p, char *report)
{
	long	time;
	long	local_time;
	long	ms_time; 
	
	pthread_mutex_lock(p->print_lock);
	printf("[%lu] philo [%lu] %s\n", dif_time(p->begin_time), p->no, report);
	pthread_mutex_unlock(p->print_lock);

}

void	eat_now(t_philo	*philo)
{
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
	report(philo, "take a fork");
	report(philo, "is eating");
	sleep_ms(philo ,philo->eat_time);
	report(philo, "is fin eating");
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(philo->spoon_left);
	pthread_mutex_unlock(philo->spoon_right);
}

void	*rout(void *av)
{
	int		count;
	long	st_time;
	t_philo	*philo;

	philo = (t_philo *) av;
	count = 1;
	st_time = get_time();
	philo->begin_time = st_time;
	philo->last_eat_time = st_time;
	while (count)
	{
		report(philo, "is thinking");
		eat_now(philo);
		count++;
		if (count == philo->eat_count)
		{
			printf("count?????\n");
			return(0);
		}
		report(philo, "is sleeping");
		sleep_ms(philo ,philo->sleep_time);
	}
	return (0);
}
