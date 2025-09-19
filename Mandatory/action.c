/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:39:27 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/19 18:39:36 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_thinking(t_philo *philo, t_data *data)
{
	return (ft_log(data, philo->id, "is thinking"));
}

int	ft_eating(t_philo *philo, t_data *data)
{
	if (ft_tmp_check_death(data))
		return (1);
	if (ft_lock(philo, data))
		return (1);
	if (ft_log(data, philo->id, "is eating"))
		return (pthread_mutex_unlock(philo->m_left_fork),
			pthread_mutex_unlock(philo->m_right_fork), 1);
	if (ft_usleep(data, data->tt_eat))
		return (pthread_mutex_unlock(philo->m_left_fork),
			pthread_mutex_unlock(philo->m_right_fork), 1);
	return (pthread_mutex_unlock(philo->m_left_fork),
		pthread_mutex_unlock(philo->m_right_fork), ft_tmp_check_death(data));
}

int	ft_lock(t_philo *philo, t_data *data)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->m_left_fork);
		if (ft_log(data, philo->id, "has taken a fork"))
			return (pthread_mutex_unlock(philo->m_left_fork), 1);
		pthread_mutex_lock(philo->m_right_fork);
		if (ft_log(data, philo->id, "has taken a fork"))
			return (pthread_mutex_unlock(philo->m_right_fork),
				pthread_mutex_unlock(philo->m_left_fork), 1);
	}
	else
	{
		pthread_mutex_lock(philo->m_right_fork);
		if (ft_log(data, philo->id, "has taken a fork"))
			return (pthread_mutex_unlock(philo->m_right_fork), 1);
		pthread_mutex_lock(philo->m_left_fork);
		if (ft_log(data, philo->id, "has taken a fork"))
			return (pthread_mutex_unlock(philo->m_left_fork),
				pthread_mutex_unlock(philo->m_right_fork), 1);
	}
	pthread_mutex_lock(&philo->m_meal_nb);
	philo->meal_nb++;
	philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->m_meal_nb);
	return (0);
}

int	ft_sleeping(t_philo *philo, t_data *data)
{
	if (ft_log(data, philo->id, "is sleeping"))
		return (1);
	if (ft_usleep(data, data->tt_sleep))
		return (1);
	return (ft_tmp_check_death(data));
}

int	ft_usleep(t_data *data, long long total)
{
	long long	tmp;

	tmp = get_timestamp();
	while (get_timestamp() - tmp < total)
	{
		if (ft_tmp_check_death(data))
			return (1);
		usleep(500);
	}
	return (0);
}
