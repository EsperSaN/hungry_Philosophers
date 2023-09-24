/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:42:16 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/24 21:14:03 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	input_checker(char **arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (!is_all_num(*arg))
			return (printf(""), 0);
		arg++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_var	var;
	int		i;

	i = -1;
	var.begin_epoch_time = get_time();
	if (ac < 5 || ac > 6)
		return (printf(ER_MSG), 1);
	if (!input_checker(av + 1))
		return (printf(INP_MSG), 1);
	if (!init_var(&var, av, ac))
		return (printf(FAIL_INIT), 1);
	while (++i < var.philo_num)
	{
		if (i % 2 == 0)
			usleep(50);
		pthread_create(&var.philo[i].philo, NULL, &rout, (void *)&var.philo[i]);
	}
	i = 0;
	while (1)
	{
		if (i == var.philo_num)
			i = 0;
		if (var.philo[i].is_die)
		{
			stop_all_phil(&var);
			break ;
		}
		i++;
	}
	while (i < var.philo_num)
	{
		pthread_join(var.philo[i].philo, NULL);
		printf("the thread [%d] end\n", i);
		i++;
	}
}
