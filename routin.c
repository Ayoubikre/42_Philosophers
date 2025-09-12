/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:47:55 by noctis            #+#    #+#             */
/*   Updated: 2025/09/12 21:14:29 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ft_routin(void *ptr)
{
	t_philo *philo;
	
	philo= (t_philo *)ptr;
	while(philo->data->ready==0)
		usleep(100);
	if(philo->id % 2!=0)
	{
		printf("thread %d is sleping \n",philo->id);
		usleep(100);
	}
	while(1)
	{
		printf("thread %d is thinking \n",philo->id);
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

		pthread_mutex_lock(&(philo->data->m_print));
		if (!philo->data->dead)
		{
			printf("%lld %d has taken a fork\n", get_timestamp() - philo->data->start, philo->id);
			printf("%lld %d has taken a fork\n", get_timestamp() - philo->data->start, philo->id);
			printf("%lld %d is eating\n", get_timestamp() - philo->data->start, philo->id);
		}
		pthread_mutex_unlock(&(philo->data->m_print));
		
		if (philo->id % 2)
		{
			pthread_mutex_unlock(philo->m_right_fork);
			pthread_mutex_unlock(philo->m_left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->m_left_fork);
			pthread_mutex_unlock(philo->m_right_fork);
		}
	}
	
	// printf("this is thread %d \n",philo->id);
	return (NULL);
}

void	*ft_monitor(void *ptr)
{
	t_data *data;
	
	data= (t_data *)ptr;
	
	printf("this is monitor and he is monitoring  %d of threds \n",data->nb);

	return (NULL);
}
