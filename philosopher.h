/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:45:04 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/17 11:24:35 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# define ER_MSG "This program accept only 4 to 5 argument\n"
# define INP_MSG "Please put the correct argument [ONLY POSITIVE INT NUMBER]\n"
# define FAIL_INIT "Fail to init the value SRY\n"

typedef struct s_philo {
	pthread_t		philo;
	int				no;
	int				die_time;
	int				time_eat;
	int				eat_time;
	int				think_time;
	int				sleep_time;
	int				eat_count;
}	t_philo;

typedef struct s_variable {
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				think_time;
	int				sleep_time;
	int				eat_count;
	pthread_mutex_t	*spoon;
	struct s_philo	*philo;
}	t_var;

int		is_all_num(char *str);
long	ft_atoi(const char *str);
int		init_var(t_var *var, char **av, int ac);
void	*rout(void *av);
#endif