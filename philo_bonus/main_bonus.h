/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:50:42 by noctis            #+#    #+#             */
/*   Updated: 2025/09/19 18:07:03 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

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

#endif
