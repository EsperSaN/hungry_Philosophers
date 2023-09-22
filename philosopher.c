/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:42:16 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/22 09:41:54 by pruenrua         ###   ########.fr       */
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
			return (printf("INPUT [%s] IS NAH ", *arg), 0);
		arg++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_var	var;
	int		i;

	i = -1;
	var.start_time = get_time();
	if (ac < 5 || ac > 6)
		return (printf(ER_MSG), 1);
	if (!input_checker(av + 1))
		return (printf(INP_MSG), 1);
	if (!init_var(&var, av, ac))
		return (printf(FAIL_INIT), 1);
	//printf("ph no: [%d]\ndie_t:[%d]\neat_time[%d]\nsleep_t[%d]\neat_count[%d]\n", var.philo_num, var.die_time, var.eat_time, var.sleep_time, var.eat_count);
	while (++i < var.philo_num)
	{
		pthread_create(&var.philo[i].philo, NULL, &rout, (void *)&var.philo[i]);
	}
	i = 0;

	while (i < var.philo_num)
	{
		pthread_join(var.philo[i].philo, NULL);
		printf("the thread [%d] end\n", i);
		i++;
	}
}
