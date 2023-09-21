/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:58:06 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/18 01:26:27 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <error.h>
void *rout(void *av)
{
	t_philo *philo ;
	
	philo = (t_philo*)av;
	usleep(2);
int count = 1;
while (count)
{
	printf("[%d] is thinking \n", philo->no);
	usleep(philo->think_time);
	if (philo->no % 2 == 0 )
	{
		pthread_mutex_lock(philo->spoon_right);
		pthread_mutex_lock(philo->spoon_left);
	}
	else
	{
		pthread_mutex_lock(philo->spoon_left);
		pthread_mutex_lock(philo->spoon_right);
	}
	printf("[%d] grap the left fork!!! \n", philo->no);
	printf("[%d] grap the right fork!!! \n", philo->no);
	printf("[%d] grap all fork!!\n",philo->no);
	usleep(philo->eat_time);
	pthread_mutex_unlock(philo->spoon_left);
	pthread_mutex_unlock(philo->spoon_right);
	philo->eat_count++;
	printf("[%d] put the fork back sry\n", philo->no);
	usleep(philo->sleep_time);
}
}