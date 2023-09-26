/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:42:16 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/26 02:45:50 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	mammy_thread_takking_care_of_all_philo(t_var *v)
{
	int	i;

	i = 0;
	while (*v->is_die == 0)
	{
		usleep(1);
		if (i == v->philo_num)
			i = 0;
		die_check(&v->philo[i]);
		i++;
	}
}

void	nfree(void *p)
{
	free(p);
	p = NULL;
}

void	let_em_free(t_var *v)
{
	int	i;

	if (v->is_die)
		nfree(v->is_die);
	if (v->philo)
		nfree(v->philo);
	if (v->all_spoon)
	{
		i = -1;
		while (++i < v->philo_num)
			pthread_mutex_destroy(&v->all_spoon[i]);
		nfree(v->all_spoon);
	}
	if (v->print_lock)
	{
		pthread_mutex_destroy(v->print_lock);
		nfree(v->print_lock);
	}
}

int	input_checker(char **arg)
{
	long	res;

	if (!arg)
		return (0);
	while (*arg)
	{
		if (!is_all_num(*arg))
			return (0);
		res = ft_atoi(*arg);
		if (res == 0 || res > INT_MAX || res < INT_MIN)
			return (0);
		arg++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_var	v;
	int		i;

	i = -1;
	v.begin_epoch_time = get_time();
	if (ac < 5 || ac > 6)
		return (printf(ER_MSG), 1);
	if (!input_checker(av + 1))
		return (printf(INP_MSG), 1);
	if (!init_var(&v, av, ac))
		return (printf(FAIL_INIT), 1);
	while (++i < v.philo_num)
	{
		if (pthread_create(&v.philo[i].philo, NULL, &rout, (void *)&v.philo[i]))
		{
			printf("Error :Thread cant be create\n");
			let_em_free(&v);
			return (1);
		}
	}
	usleep(5);
	mammy_thread_takking_care_of_all_philo(&v);
	i = -1;
	while (++i < v.philo_num)
		pthread_join(v.philo[i].philo, NULL);
	let_em_free(&v);
	return (1);
}
