/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:50:42 by noctis            #+#    #+#             */
/*   Updated: 2025/08/27 18:58:54 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

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
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_n;
	long long		meals_ts;
	pthread_t		th;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	*m_left_fork;
	pthread_mutex_t	*m_right_fork;
	t_data			*data;

}					t_philo;

#endif