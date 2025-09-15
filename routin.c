/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:47:55 by noctis            #+#    #+#             */
/*   Updated: 2025/09/15 17:44:15 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int tmp_check_death(t_data *data)
{
	pthread_mutex_lock(&data->m_dead);
		if(data->dead == 1)
			return (pthread_mutex_unlock(&data->m_dead), 1);
	pthread_mutex_unlock(&data->m_dead);
	return 0;
}

void	*ft_routin(void *ptr)
{
	t_philo *philo;
	t_data *data;
	
	philo= (t_philo *)ptr;
	data=philo->data;


	printf("this is thread %d \n",philo->id);
	while(1)
		if(tmp_check_death(data)==1)
			return NULL;

}


























// --------------------------------------------------



// void	*ft_monitor(void *ptr)
// {
// 	t_data *data;
	
// 	data= (t_data *)ptr;
	
// 	printf("this is monitor and he is monitoring  %d threds \n",data->nb);

// 	return (NULL);
// }

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
			pthread_mutex_lock(&data->philo[i].m_meal);
			since_meal = get_timestamp() - data->philo[i].last_meal_time;
			if (since_meal > data->tt_die)
			{
				pthread_mutex_lock(&data->m_dead);
				if (!data->dead)
				{
					data->dead = 1;
					pthread_mutex_lock(&data->m_print);
					printf("%lld %d died\n", get_timestamp() - data->start, data->philo[i].id);
					pthread_mutex_unlock(&data->m_print);
				}
				pthread_mutex_unlock(&data->m_dead);
				pthread_mutex_unlock(&data->philo[i].m_meal);
				return (NULL);
			}
			if (data->must_eat != -1 && data->philo[i].meal_nb >= data->must_eat)
				full++;
			pthread_mutex_unlock(&data->philo[i].m_meal);
			i++;
		}
		if (data->must_eat != -1 && full == data->nb)
		{
			pthread_mutex_lock(&data->m_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->m_dead);
			return (NULL);
		}
		usleep(100);
	}
}