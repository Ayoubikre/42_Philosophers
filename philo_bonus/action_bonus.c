/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:32:36 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/22 16:32:57 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	ft_log(t_data *data, int id, char *msg)
{
	sem_wait(data->m_print);
	printf("%lld %d %s\n", get_timestamp() - data->start_time, id, msg);
	sem_post(data->m_print);
}

void	ft_thinking(t_data *data, t_philo *philo)
{
	ft_log(data, philo->id, "is thinking");
}

void	ft_eating(t_data *data, t_philo *philo)
{
	sem_wait(data->m_forks);
	ft_log(data, philo->id, "has taken a fork");
	sem_wait(data->m_forks);
	ft_log(data, philo->id, "has taken a fork");
	sem_wait(data->m_meal_nb);
	philo->meal_nb++;
	philo->last_meal_time = get_timestamp();
	sem_post(data->m_meal_nb);
	ft_log(data, philo->id, "is eating");
	usleep(data->tt_eat * 1000);
	sem_post(data->m_forks);
	sem_post(data->m_forks);
}

void	ft_sleeping(t_data *data, t_philo *philo)
{
	ft_log(data, philo->id, "is sleeping");
	usleep(data->tt_sleep * 1000);
}
