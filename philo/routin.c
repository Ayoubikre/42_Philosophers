/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:47:55 by noctis            #+#    #+#             */
/*   Updated: 2025/09/23 17:03:47 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ft_routin_one(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	ft_log(data, philo->id, "is thinking");
	pthread_mutex_lock(philo->m_left_fork);
	ft_log(data, philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->m_left_fork);
	usleep(data->tt_die * 1000);
	return (NULL);
}

void	*ft_routin(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!ft_tmp_check_death(data))
	{
		if (ft_thinking(philo, data))
			return (NULL);
		if (ft_eating(philo, data))
			return (NULL);
		if (ft_sleeping(philo, data))
			return (NULL);
	}
	return (NULL);
}
