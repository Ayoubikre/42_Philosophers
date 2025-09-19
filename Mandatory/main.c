/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:19:10 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/19 17:40:51 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_philo(t_data *data, int i)
{
	if (data->nb == 1)
	{
		pthread_create(&(data->philo[i].th), NULL, ft_routin_one,
			(void *)&(data->philo[i]));
	}
	else
	{
		while (i < data->nb)
		{
			pthread_create(&(data->philo[i].th), NULL, ft_routin,
				(void *)&(data->philo[i]));
			i++;
		}
	}
	pthread_create(&(data->monitor), NULL, ft_monitor, (void *)data);
	data->ready = 1;
	i = 0;
	while (i < data->nb)
	{
		pthread_join(data->philo[i].th, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	return (0);
}

int	main(int ac, char **ar)
{
	t_data	data;

	if (ft_init(&data, ac, ar, 0) == -1)
		return (-1);
	ft_philo(&data, 0);
	return (ft_clean(&data), 0);
}
