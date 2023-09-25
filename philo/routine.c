/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:58:06 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/25 02:58:35 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
void	sleep_ms(t_philo *p, size_t ms)
{
	long	ms_time_now;
	long	dif;

	p->p_time = get_time();
	dif = 0;
	if (*p->is_die == 1)
		return ;
	while (dif < ms)
	{
		if (dif_time(p->last_eat_time) > p->die_time)
		{
			pthread_mutex_lock(p->print_lock);
			if (*p->is_die == 0)
				printf("%lu    %d    died\n", dif_time(p->begin_time), p->no);
			*p->is_die = 1;
			pthread_mutex_unlock(p->print_lock);
		}
		dif = dif_time(p->p_time);
		usleep(5);
	}
}

void	report(t_philo *p, char *report)
{
	long	time;
	long	local_time;
	long	ms_time;

	pthread_mutex_lock(p->print_lock);
	if (*p->is_die == 0)
		printf("%lu    %d    %s\n", dif_time(p->begin_time), p->no, report);
	pthread_mutex_unlock(p->print_lock);
}

void	eat_now(t_philo	*philo)
{
	if (*philo->is_die == 1)
		return ;
	if (philo->no % 2 == 0)
	{
		pthread_mutex_lock(philo->spoon_right);
		report(philo, "take right fork");
		pthread_mutex_lock(philo->spoon_left);
		report(philo, "take left fork");
	}
	else
	{
		pthread_mutex_lock(philo->spoon_left);
		report(philo, "take left fork");
		pthread_mutex_lock(philo->spoon_right);
		report(philo, "take right fork");
	}
	report(philo, "has taken a fork");
	report(philo, "is eating");
	sleep_ms(philo, philo->eat_time);
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
	pid_t x = syscall(__NR_gettid);

	printf("p [%d] thread id [%lu]\n", philo->no, x );
	while (*philo->is_start == 0)
		usleep(1);
	count = 0;
	st_time = get_time();
	printf("start time [%lu]\n", st_time);
	philo->last_eat_time = st_time;
	philo->begin_time = st_time;
	while (*philo->is_die == 0)
	{
		report(philo, "is thinking");
		eat_now(philo);
		count++;
		if (count == philo->eat_count)
			return (0);
		report(philo, "is sleeping");
		sleep_ms(philo, philo->sleep_time);
	}
	return (0);
}
