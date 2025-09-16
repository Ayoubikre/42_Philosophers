/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:29:25 by noctis            #+#    #+#             */
/*   Updated: 2025/09/16 14:16:03 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// void ft_usleep(long long time) {
//     long long start = get_current_time();
// Similar to get_timestamp but absolute
//     while (get_current_time() - start < time) {
//         usleep(50);  // Small sleeps to check often
//     }
// }

// void print_status(t_philo *philo, char *msg) {
//     pthread_mutex_lock(&philo->data->print_mutex);
//     if (philo->data->stop_flag == 0) {
// Only print if simulation not stopped
//         printf("%lld %d %s\n", get_timestamp(philo->data), philo->id, msg);
//     }
//     pthread_mutex_unlock(&philo->data->print_mutex);
// }

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	signe;

	result = 0;
	signe = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * signe);
}

int	ft_is_N_digit(int c)
{
	if ('0' <= c && c <= '9')
		return (0);
	return (1);
}

void	ft_free(t_data *data)
{
	free(data->m_forks);
	free(data->philo);
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_print);
	while (i < data->nb)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		pthread_mutex_destroy(&data->philo[i].m_meal_nb);
		i++;
	}
	ft_free(data);
}
