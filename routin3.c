/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 09:04:26 by noctis            #+#    #+#             */
/*   Updated: 2025/09/19 00:43:48 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int ft_tmp_check_death(t_data *data)
{
    pthread_mutex_lock(&data->m_dead);
    if(data->dead)
        return(pthread_mutex_unlock(&data->m_dead), 1);
    return(pthread_mutex_unlock(&data->m_dead), 0);
}

int ft_log(t_data *data, int id, char*msg)
{
    pthread_mutex_lock(&data->m_print);
        if(ft_tmp_check_death(data))
            return (pthread_mutex_unlock(&data->m_print), 1);
        printf("%lld %d %s\n", get_timestamp() - data->start_time, id, msg);
    pthread_mutex_unlock(&data->m_print);
    return (ft_tmp_check_death(data));
    // return 0;
}

void ft_usleep(t_data *data, long long t)
{
    long long t2=0;
    while(t2<t)
    {
        usleep(500);
        t2+=500;
    }
}

void	*ft_routin_one(void *ptr)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)ptr;
    data = philo->data;
    ft_log(data, philo->id, "is thinking");
    pthread_mutex_lock(philo->m_left_fork);
    ft_log(data, philo->id,"has taken a fork");
    pthread_mutex_unlock(philo->m_left_fork);
    ft_usleep(data, data->tt_die*1000);
    pthread_mutex_lock(&data->m_dead);
        data->dead=1;
    pthread_mutex_unlock(&data->m_dead);
    return NULL; 
}

int ft_thinking(t_philo *philo, t_data *data)
{
    return (ft_log(data, philo->id,"is thinking"));
}

int ft_eating(t_philo *philo, t_data *data)
{
    if(ft_tmp_check_death(data)==-1)
        return 1;
    if(philo->id % 2!=0)
    {
        pthread_mutex_lock(philo->m_left_fork);
        if(ft_log(data, philo->id,"has taken a fork"))
            return 1;
        pthread_mutex_lock(philo->m_right_fork);
        if(ft_log(data, philo->id,"has taken a fork"))
            return 1;
    }
    else
    {
        pthread_mutex_lock(philo->m_right_fork);
        if(ft_log(data, philo->id,"has taken a fork"))
            return 1;
        pthread_mutex_lock(philo->m_left_fork);
        if(ft_log(data, philo->id,"has taken a fork"))
            return 1;
    }
    
    pthread_mutex_lock(&philo->m_meal_nb);
        philo->meal_nb++;
        philo->last_meal_time=get_timestamp();
    pthread_mutex_unlock(&philo->m_meal_nb);
    
    if(ft_log(data, philo->id,"is eating"))
        return 1;
    ft_usleep(data, data->tt_eat*1000);
    
    pthread_mutex_unlock(philo->m_right_fork);
    pthread_mutex_unlock(philo->m_left_fork);
    
    return (ft_tmp_check_death(data));
    // return 0;
}

int ft_sleeping(t_philo *philo, t_data *data)
{
    if(ft_log(data, philo->id,"is sleeping"))
        return 1;
    ft_usleep(data, data->tt_sleep*1000);
    
    return (ft_tmp_check_death(data));
    // return 0;
}


void	*ft_routin(void *ptr)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)ptr;
    data = philo->data;
    
    if(philo->id % 2==0)
        usleep(50);
    while(1)
    {
        if(ft_tmp_check_death(data))
            break;
        if(ft_thinking(philo, data))
            break;
        if(ft_eating(philo, data))
            break;
        if(ft_sleeping(philo, data))
            break;

        // ft_thinking(philo, data);
        // ft_eating(philo, data);
        // ft_sleeping(philo, data);
    }
    return NULL;
}




































// void	*ft_monitor(void *arg)
// {
//     t_data *data;

//     data = (t_data *)arg;

    

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