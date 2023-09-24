/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:51:24 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/24 21:14:02 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	stop_all_phil(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->philo_num)
	{
		pthread_mutex_destroy(&var->all_spoon[i]);
		i++;
	}
	i = 0;
	while (i < var->philo_num)
	{
		printf("assign die to [%d]\n", i);
		var->philo[i].is_die = 1;
		i++;
	}
}
