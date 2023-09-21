/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:45:04 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/18 01:33:58 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define ER_MSG "This program accept only 4 to 5 argument\n"
# define INP_MSG "Please put the correct argument [ONLY POSITIVE INT NUMBER]\n"
# define FAIL_INIT "Fail to init the value SRY\n"
# define INIT_S_ER "Fail to init the main struct\n"

typedef struct s_philo {
	pthread_t		philo;
	long			no;
	long			last_eat;
	long			start_time;
	long			die_time;
	long			time_eat;
	long			eat_time;
	long			think_time;
	long			sleep_time;
	pthread_mutex_t	*spoon_left;
	pthread_mutex_t	*spoon_right;
	long			eat_count;
}	t_philo;

typedef struct s_variable {
	long				philo_num;
	long				die_time;
	long				eat_time;
	long				think_time;
	long				sleep_time;
	long				eat_count;
	pthread_mutex_t	*all_spoon;
	struct s_philo	*philo;
}	t_var;

int		is_all_num(char *str);
long	ft_atoi(const char *str);
int		init_var(t_var *var, char **av, int ac);
void	*rout(void *av);
#endif