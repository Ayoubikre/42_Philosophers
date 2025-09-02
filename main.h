/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:50:42 by noctis            #+#    #+#             */
/*   Updated: 2025/09/02 18:28:35 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				must_eat;

	long long		start;
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
	pthread_mutex_t	m_meal;
	pthread_mutex_t	*m_left_fork;
	pthread_mutex_t	*m_right_fork;
	t_data			*data;

}					t_philo;

int					main(int ac, char **ar);
int					ft_init(t_data *data, int ac, char **ar, int i);


// --------------------utils
long long			get_timestamp(void);
int					ft_atoi(const char *str);
int					ft_is_N_digit(int c);
void				ft_free(t_data *data);
void				ft_clean(t_data *data);

// --------------------routin

void				*ft_routin(void *ptr);

void				*ft_monitor(void *ptr);

#endif