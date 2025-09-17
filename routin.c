/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:47:55 by noctis            #+#    #+#             */
/*   Updated: 2025/09/17 09:11:24 by noctis           ###   ########.fr       */
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

void ft_log(t_data *data , int nb, char *t)
{
	pthread_mutex_lock(&data->m_print);
		if(tmp_check_death(data) == 0)
			printf("%lld %d %s", get_timestamp()-data->start_time , nb, t);
	pthread_mutex_unlock(&data->m_print);

}

int ft_eat(t_data *data, t_philo *philo)
{
	if(philo->id % 2 !=0)
	{
		pthread_mutex_lock(philo->m_left_fork);
		pthread_mutex_lock(philo->m_right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->m_right_fork);
		pthread_mutex_lock(philo->m_left_fork);
	}
	if(tmp_check_death(data))
		return 1;
	ft_log(data, philo->id, "has taken a fork\n");
	ft_log(data, philo->id, "has taken a fork\n");
	ft_log(data, philo->id, "is eating\n");
	
	pthread_mutex_lock(&philo->m_meal_nb);
		philo->meal_nb++;
		philo->last_meal_time=get_timestamp();
	pthread_mutex_unlock(&philo->m_meal_nb);
	
	usleep(data->tt_eat*1000);
	
	if(philo->id % 2 !=0)
	{
		pthread_mutex_unlock(philo->m_right_fork);
		pthread_mutex_unlock(philo->m_left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->m_left_fork);
		pthread_mutex_unlock(philo->m_right_fork);
	}
	return (tmp_check_death(data));
}

// int ft_sleep(t_data *data, t_philo *philo)
// {
// 	long long time=0;
// 	ft_log(data, philo->id, "is sleeping\n");
	
// 	while(time < data->tt_sleep*1000)
// 	{
// 		if(tmp_check_death(data))
// 			return 1;	
// 		time+=50;
// 		usleep(50);
// 	}
// 	return (tmp_check_death(data));
// }

int ft_sleep(t_data *data, t_philo *philo)
{
	ft_log(data, philo->id, "is sleeping\n");
	usleep(data->tt_sleep*1000);
	return (tmp_check_death(data));
}


void	*ft_routin(void *ptr)
{
	t_philo *philo;
	t_data *data;
	
	philo= (t_philo *)ptr;
	data=philo->data;

	if(philo->id % 2 == 0)
		if(ft_sleep(data, philo))
			return NULL;
	
	int i=0;
	while(!tmp_check_death(data))
	{
		ft_log(data, philo->id, "is Thinking\n");
		if(ft_eat(data, philo))
			return NULL;
		if(ft_sleep(data, philo))
			return NULL;
		i++;

	}
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