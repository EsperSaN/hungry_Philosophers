/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:45:04 by pruenrua          #+#    #+#             */
/*   Updated: 2023/09/22 09:58:52 by pruenrua         ###   ########.fr       */
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
	size_t			no;
	size_t			last_eat;
	size_t			start_time;
	size_t			die_time;
	size_t			time_eat;
	size_t			eat_time;
	size_t			think_time;
	size_t			sleep_time;
	pthread_mutex_t	*start;
	pthread_mutex_t	*spoon_left;
	pthread_mutex_t	*spoon_right;
	size_t			eat_count;
}	t_philo;

typedef struct s_variable {
	size_t				philo_num;
	size_t				die_time;
	size_t				eat_time;
	size_t				think_time;
	size_t				sleep_time;
	size_t				eat_count;
	size_t				start_time;
	pthread_mutex_t		*start;
	pthread_mutex_t		*all_spoon;
	struct s_philo		*philo;
}	t_var;


size_t	get_time(void);
void	sleep_ms(size_t milisec);
int		is_all_num(char *str);
long	ft_atoi(const char *str);
int		init_var(t_var *var, char **av, int ac);
void	*rout(void *av);
#endif