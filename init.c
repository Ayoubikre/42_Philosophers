/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:07:24 by noctis            #+#    #+#             */
/*   Updated: 2025/09/02 18:10:02 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_check(int ac, char **ar)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (ar[i][j])
		{
			if (ft_is_N_digit(ar[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		philo[i].id = i + 1;
		philo[i].meal_nb = 0;
		philo[i].last_meal_time = data->start;
		pthread_mutex_init(&philo[i].m_meal, NULL);
		philo[i].m_left_fork = &data->m_forks[(i) % data->nb];
		philo[i].m_right_fork = &data->m_forks[(i + 1) % data->nb];
		philo[i].data = data;
		i++;
	}
}

int	ft_init(t_data *data, int ac, char **ar, int i)
{
	if (ac < 5 || ac > 6 || ft_check(ac, ar) == -1)
		return (printf("ERROR : Invalid Arguments\n"), -1);
	data->nb = ft_atoi(ar[1]);
	data->tt_die = ft_atoi(ar[2]);
	data->tt_eat = ft_atoi(ar[3]);
	data->tt_sleep = ft_atoi(ar[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(ar[5]);
	data->start = get_timestamp();
	data->dead = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->nb);
	if (!data->m_forks || !data->philo)
		return (ft_free(data), -1);
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	while (i < data->nb)
	{
		pthread_mutex_init(&data->m_forks[i], NULL);
		i++;
	}
	ft_init_philo(data, data->philo);
	return (0);
}
