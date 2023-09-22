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

void	report(t_philo *p, char *report)
{
	size_t	time;

	pthread_mutex_lock(p->start);
	time = get_time() - p->start_time;
	if ((get_time() - p->last_eat) >= p->die_time)
	{
		printf("[%lu] philo [%lu] DIES \n", time, p->no);
		exit(0);
	}
	printf("[%lu] philo [%lu] %s\n", time, p->no, report);
	pthread_mutex_unlock(p->start);
}

void	hungry_now(t_philo	*philo)
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
	sleep_ms(philo->eat_time);
	pthread_mutex_unlock(philo->spoon_left);
	pthread_mutex_unlock(philo->spoon_right);
	philo->last_eat = get_time();
	report(philo, "is eating");
	philo->eat_count++;
}

void	*rout(void *av)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *) av;
	printf("hi im [%ld]\n", philo->no);
	count = 1;

	//while (*philo->start == 0)
	//	;

	while (count)
	{
		hungry_now(philo);
		report(philo, "is thingking");
		sleep_ms(philo->think_time);	
		report(philo, "is slipping");
		sleep_ms(philo->sleep_time);
	}
	return (0);
}
