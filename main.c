/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:19:10 by aakritah          #+#    #+#             */
/*   Updated: 2025/08/28 06:03:46 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_philo(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&(data->monitor), NULL, ft_routin_m, (void *)data) != 0)
		return (-1);
	while (i < data->nb)
	{
		if (pthread_create(&(data->philo[i].th), NULL, ft_routin,
				(void *)data) != 0)
		{
			while (--i < 0)
				pthread_join(data->philo[i].th, NULL);
			return (pthread_join(data->monitor, NULL), -1);
		}
		i++;
	}
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
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	if (ft_init(data, ac, ar) == -1)
		return (ft_free(data), -1);
	if (ft_philo(data) == -1)
		return (ft_clean(data), -1);
	return (ft_clean(data), 0);
}
