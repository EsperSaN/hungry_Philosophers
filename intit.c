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
	var->philo = calloc(sizeof(t_philo), var->philo_num);
	if (var->philo == NULL)
		return (printf("INIT_S_ER"), 0);
	var->all_spoon = calloc();
	int i = 0;
	while (i < var->philo_num)
	{
		var->philo[i].no = i;
		var->philo[i].die_time = var->die_time;
		var->philo[i].eat_time = var->eat_time;
		var->philo[i].sleep_time = var->sleep_time;
		var->philo[i].eat_count = var ->eat_count;
		i++;
	}
	return (1);
}
