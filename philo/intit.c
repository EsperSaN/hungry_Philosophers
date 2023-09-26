/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:14:21 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/26 02:47:37 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_argument(t_var *var, char **av, int ac)
{
	var->philo_num = ft_atoi(av[1]);
	var->die_time = ft_atoi(av[2]);
	var->eat_time = ft_atoi(av[3]);
	var->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		var->eat_count = ft_atoi(av[5]);
	else
		var->eat_count = -1;
}

int	allocate_data(t_var *var)
{
	var->is_die = ft_calloc(sizeof(int), 1);
	if (var->is_die == NULL)
		return (0);
	var->is_start = ft_calloc(sizeof(int), 1);
	if (var->is_start == NULL)
		return (0);
	var->philo = ft_calloc(sizeof(t_philo), var->philo_num);
	if (var->philo == NULL)
		return (0);
	var->all_spoon = ft_calloc(sizeof(pthread_mutex_t), var->philo_num);
	if (var->all_spoon == NULL)
		return (0);
	var->print_lock = ft_calloc(sizeof(pthread_mutex_t), 1);
	if (var->print_lock == NULL)
		return (0);
	return (1);
}

int	init_data(t_var *var)
{
	int	i;

	i = 0;
	*var->is_die = 0;
	*var->is_start = 0;
	while (i < var->philo_num)
	{
		if (pthread_mutex_init(&var->all_spoon[i], NULL) != 0)
			return (printf("vary error fail to init the spoon\n"), 0);
		i++;
	}
	if (pthread_mutex_init(var->print_lock, NULL) != 0)
		return (printf("vary error fail to init the print_lock\n"), 0);

	return (1);
}

void	assign_philo_data(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->philo_num)
	{
		var->philo[i].no = i + 1;
		var->philo[i].die_time = var->die_time;
		var->philo[i].eat_time = var->eat_time;
		var->philo[i].sleep_time = var->sleep_time;
		var->philo[i].eat_count = var->eat_count;
		var->philo[i].spoon_left = &var->all_spoon[i];
		var->philo[i].begin_time = var->begin_epoch_time;
		var->philo[i].print_lock = var->print_lock;
		var->philo[i].is_die = var->is_die;
		var->philo[i].is_start = var->is_start;
		if (i == (var->philo_num - 1))
			var->philo[i].spoon_right = &var->all_spoon[0];
		else
			var->philo[i].spoon_right = &var->all_spoon[i + 1];
		if (var->philo_num == 1)
		{
			var->philo[i].spoon_left = NULL;
			var->philo[i].spoon_right = NULL;
		}
		i++;
	}
}

int	init_var(t_var *var, char **av, int ac)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	init_argument(var, av, ac);
	if (!allocate_data(var))
		return (0);
	if (!init_data(var))
		return (0);
	assign_philo_data(var);
	return (1);
}
