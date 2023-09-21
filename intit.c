/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:14:21 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/18 01:34:21 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_var(t_var *var, char **av, int ac)
{
	if (!var)
		return (0);
	var->philo_num = ft_atoi(av[1]);
	var->die_time = ft_atoi(av[2]);
	var->eat_time = ft_atoi(av[3]);
	var->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		var->eat_count = ft_atoi(av[5]);
	else
		var->eat_count = -1;
	var->philo = calloc(sizeof(t_philo), var->philo_num);
	if (var->philo == NULL)
		return (printf("INIT_S_ER"), 0);
	var->all_spoon = calloc(sizeof(pthread_mutex_t), var->philo_num);
	int i = 0;
	while (i < var->philo_num)
	{
		if (pthread_mutex_init(&var->all_spoon[i], NULL) != 0)
			return (printf("vary error fail to init the spoon\n"), 1);
		i++;
	}
	i = 0;
	while (i < var->philo_num)
	{
		var->philo[i].no = i;
		var->philo[i].die_time = var->die_time;
		var->philo[i].eat_time = var->eat_time;
		var->philo[i].sleep_time = var->sleep_time;
		var->philo[i].eat_count = var->eat_count;
		printf("assigned the [%d] fork to left [%d]\n", i, i);
		var->philo[i].spoon_left = &var->all_spoon[i];
		if (i == (var->philo_num - 1))
		{
			printf("assigned the [%d] fork to right [%d]\n", 0, i);
			var->philo[i].spoon_right = &var->all_spoon[0];
		}
		else
		{
			printf("assigned the [%d] fork to right [%d]\n", i+1, i);
			var->philo[i].spoon_right = &var->all_spoon[i + 1];
		}
		i++;
	}
	exit(1);
	return (1);
}
