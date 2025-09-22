/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:43:56 by noctis            #+#    #+#             */
/*   Updated: 2025/09/22 19:50:39 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	ft_routin(t_data *data, t_philo *philo)
{
	pthread_create(&philo->monitor, NULL, ft_monitor, (void *)data);
	pthread_detach(philo->monitor);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		ft_thinking(data, philo);
		ft_eating(data, philo);
		if (data->meal_max != -1 && data->philo->meal_nb >= data->meal_max)
			exit(0);
		ft_sleeping(data, philo);
	}
}

void	*ft_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->m_dead);
		if (get_timestamp() - data->philo->last_meal_time > data->tt_die)
		{
			sem_wait(data->m_print);
			printf("%lld %d %s\n", get_timestamp() - data->start_time,
				data->philo->id, RED "died" RESET);
			exit(1);
		}
		sem_post(data->m_dead);
		usleep(500);
	}
	return (NULL);
}
