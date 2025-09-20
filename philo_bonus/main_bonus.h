/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:50:42 by noctis            #+#    #+#             */
/*   Updated: 2025/09/20 02:12:52 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\e[1;31m"
# define RESET "\e[0m"

typedef struct s_data
{
	int				nb;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				meal_max;

	long long		start_time;
	int				dead;
	pid_t			*pid;
	sem_t			*m_forks;
	sem_t			*m_print;
	sem_t			*m_dead;
	sem_t			*m_meal_nb;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meal_nb;
	long long		last_meal_time;
	pthread_t		monitor;
}					t_philo;

//------------------------- Main :
int					main(int ac, char **ar);
// int					ft_philo(t_data *data, int i);

//------------------------- Init :
int					ft_init(t_data *data, int ac, char **ar, int i);
int					ft_init_sem(t_data *data);
int					ft_check(int ac, char **ar);
long long			get_timestamp(void);

//------------------------- Routin :

//------------------------- Monitore :

//------------------------- Action :

//------------------------- Utils :
int					ft_atoi(const char *str);
int					ft_is_n_digit(int c);
void				ft_clean(t_data *data);

#endif
