/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:56:21 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/16 14:13:02 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ft_monitor(void *arg)
{
	t_data		*data;
	int			i;
	int			full;
	long long	since_meal;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		full = 0;
		while (i < data->nb)
		{
			pthread_mutex_lock(&data->philo[i].m_meal_nb);
			since_meal = get_timestamp() - data->philo[i].last_meal_time;
			if (since_meal > data->tt_die)
			{
				pthread_mutex_lock(&data->m_dead);
				if (!data->dead)
				{
					data->dead = 1;
					pthread_mutex_lock(&data->m_print);
					printf("%lld %d died\n", get_timestamp() - data->start_time, data->philo[i].id);
					pthread_mutex_unlock(&data->m_print);
				}
				pthread_mutex_unlock(&data->m_dead);
				pthread_mutex_unlock(&data->philo[i].m_meal_nb);
				return (NULL);
			}
			if (data->meal_max != -1 && data->philo[i].meal_nb >= data->meal_max)
				full++;
			pthread_mutex_unlock(&data->philo[i].m_meal_nb);
			i++;
		}
		if (data->meal_max != -1 && full == data->nb)
		{
			pthread_mutex_lock(&data->m_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->m_dead);
			return (NULL);
		}
		usleep(100);
	}
}

void	*ft_routin(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	long long	tmp_start;

	philo = (t_philo *)arg;
	data = philo->data;

	// Stagger start for even philosophers
	if (philo->id % 2 == 0)
		usleep(1000);

	while (1)
	{
		// Check if simulation ended
		pthread_mutex_lock(&data->m_dead);
		if (data->dead)
			return (pthread_mutex_unlock(&data->m_dead), NULL);
		pthread_mutex_unlock(&data->m_dead);

		// THINKING
		pthread_mutex_lock(&data->m_print);
		if (!data->dead)
			printf("%lld %d is thinking\n", get_timestamp() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->m_print);

		// Special case: only one philosopher
		if (data->nb == 1)
		{
			pthread_mutex_lock(philo->m_left_fork);
			pthread_mutex_lock(&data->m_print);
			if (!data->dead)
				printf("%lld %d has taken a fork\n", get_timestamp() - data->start_time, philo->id);
			pthread_mutex_unlock(&data->m_print);
			while (1)
			{
				pthread_mutex_lock(&data->m_dead);
				if (data->dead)
					return (pthread_mutex_unlock(&data->m_dead), NULL);
				pthread_mutex_unlock(&data->m_dead);
				usleep(100);
			}
		}

		// Pick forks (odd/even strategy to avoid deadlock)
		if (philo->id % 2)
		{
			pthread_mutex_lock(philo->m_left_fork);
			pthread_mutex_lock(philo->m_right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->m_right_fork);
			pthread_mutex_lock(philo->m_left_fork);
		}

		// Log fork + eating
		pthread_mutex_lock(&data->m_print);
		if (!data->dead)
		{
			printf("%lld %d has taken a fork\n", get_timestamp() - data->start_time, philo->id);
			printf("%lld %d has taken a fork\n", get_timestamp() - data->start_time, philo->id);
			printf("%lld %d is eating\n", get_timestamp() - data->start_time, philo->id);
		}
		pthread_mutex_unlock(&data->m_print);

		// Update meal info
		pthread_mutex_lock(&philo->m_meal_nb);
		philo->last_meal_time = get_timestamp();
		philo->meal_nb++;
		pthread_mutex_unlock(&philo->m_meal_nb);

		// Death-aware eating sleep
		tmp_start = get_timestamp();
		while (get_timestamp() - tmp_start < data->tt_eat)
		{
			pthread_mutex_lock(&data->m_dead);
			if (data->dead)
				return (pthread_mutex_unlock(&data->m_dead), NULL);
			pthread_mutex_unlock(&data->m_dead);
			usleep(100);
		}

		pthread_mutex_unlock(philo->m_left_fork);
		pthread_mutex_unlock(philo->m_right_fork);

		// SLEEPING
		pthread_mutex_lock(&data->m_print);
		if (!data->dead)
			printf("%lld %d is sleeping\n", get_timestamp() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->m_print);

		tmp_start = get_timestamp();
		while (get_timestamp() - tmp_start < data->tt_sleep)
		{
			pthread_mutex_lock(&data->m_dead);
			if (data->dead)
				return (pthread_mutex_unlock(&data->m_dead), NULL);
			pthread_mutex_unlock(&data->m_dead);
			usleep(100);
		}
	}
	return (NULL);
}
