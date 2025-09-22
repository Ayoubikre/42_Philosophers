/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:39:17 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/22 19:44:45 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_tmp_check_death(t_data *data)
{
	pthread_mutex_lock(&data->m_dead);
	if (data->dead)
		return (pthread_mutex_unlock(&data->m_dead), 1);
	return (pthread_mutex_unlock(&data->m_dead), 0);
}

int	ft_log(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->m_print);
	if (!ft_tmp_check_death(data))
		printf("%lld %d %s\n", get_timestamp() - data->start_time, id, msg);
	return (pthread_mutex_unlock(&data->m_print), ft_tmp_check_death(data));
}

int	ft_monitor_2(t_data *data, int i, int *count)
{
	t_philo		*philo;
	long long	tmp;

	while (i < data->nb)
	{
		philo = &data->philo[i];
		pthread_mutex_lock(&philo->m_meal_nb);
		tmp = get_timestamp();
		if (tmp - philo->last_meal_time > data->tt_die)
		{
			pthread_mutex_lock(&data->m_print);
			pthread_mutex_lock(&data->m_dead);
			data->dead = 1;
			printf(RED "%lld %d died\n" RESET, tmp - data->start_time,
				philo->id);
			return (pthread_mutex_unlock(&data->m_dead),
				pthread_mutex_unlock(&data->m_print),
				pthread_mutex_unlock(&philo->m_meal_nb), 1);
		}
		if (data->meal_max != -1 && data->meal_max <= philo->meal_nb)
			(*count)++;
		pthread_mutex_unlock(&philo->m_meal_nb);
		i++;
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		count;

	data = (t_data *)arg;
	while (1)
	{
		count = 0;
		if (ft_monitor_2(data, 0, &count))
			return (NULL);
		if (data->meal_max != -1 && data->nb == count)
		{
			pthread_mutex_lock(&data->m_dead);
			data->dead = 1;
			return (pthread_mutex_unlock(&data->m_dead), NULL);
		}
		usleep(500);
	}
	return (NULL);
}
