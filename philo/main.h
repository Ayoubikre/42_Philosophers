/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:50:42 by noctis            #+#    #+#             */
/*   Updated: 2025/09/19 17:55:26 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
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

	int				ready;
	long long		start_time;
	int				dead;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*m_forks;
	pthread_t		monitor;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meal_nb;
	long long		last_meal_time;
	pthread_t		th;
	pthread_mutex_t	m_meal_nb;
	pthread_mutex_t	*m_left_fork;
	pthread_mutex_t	*m_right_fork;
	t_data			*data;
}					t_philo;

//------------------------- Main :
int					main(int ac, char **ar);
int					ft_philo(t_data *data, int i);

//------------------------- Init :
int					ft_init(t_data *data, int ac, char **ar, int i);
void				ft_init_philo(t_data *data, t_philo *philo);
int					ft_check(int ac, char **ar);
long long			get_timestamp(void);

//------------------------- Routin :
void				*ft_routin(void *ptr);
void				*ft_routin_one(void *ptr);

//------------------------- Monitore :
void				*ft_monitor(void *arg);
int					ft_monitor_2(t_data *data, int i, int *count);
int					ft_log(t_data *data, int id, char *msg);
int					ft_tmp_check_death(t_data *data);

//------------------------- Action :
int					ft_thinking(t_philo *philo, t_data *data);
int					ft_eating(t_philo *philo, t_data *data);
int					ft_lock(t_philo *philo, t_data *data);
int					ft_sleeping(t_philo *philo, t_data *data);
int					ft_usleep(t_philo *philo, t_data *data, long long total);

//------------------------- Utils :
int					ft_atoi(const char *str);
int					ft_is_n_digit(int c);
void				ft_free(t_data *data);
void				ft_clean(t_data *data);

#endif
