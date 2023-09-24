/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:58:06 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/24 21:13:43 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	report(t_philo *p, char *report)
{
	long	time;
	long	local_time;
	long	ms_time;

	if (p->is_die == 1)
		return ;
	if (pthread_mutex_lock(p->print_lock))
		return ;
	printf("[%ld] philo [%d] %s\n", dif_time(p->begin_time), p->no, report);
	pthread_mutex_unlock(p->print_lock);
}

void	eat_now(t_philo	*philo)
{
	if (philo->no % 2 == 0 && philo->is_die == 0)
	{
		pthread_mutex_lock(philo->spoon_right);
		pthread_mutex_lock(philo->spoon_left);
	}
	else if (philo->is_die == 0)
	{
		pthread_mutex_lock(philo->spoon_left);
		pthread_mutex_lock(philo->spoon_right);
	}
	else
		return ;
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
	count = 1;
	st_time = get_time();
	philo->last_eat_time = st_time;
	while (philo->is_die == 0)
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
