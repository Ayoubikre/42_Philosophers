/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:05:21 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/22 04:11:56 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	ft_wait(t_data *data, int i, int s, int j)
{
	while (i < data->nb)
	{
		waitpid(-1, &s, 0);
		if (WEXITSTATUS(s) != 0)
		{
			j = 0;
			while (j < data->nb)
			{
				kill(data->pid[j], SIGTERM);
				j++;
			}
			break ;
		}
		i++;
	}
}

int	ft_philo(t_data *data, int i)
{
	t_philo	philo;

	while (i < data->nb)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			(ft_clean(data), exit(1));
		else if (data->pid[i] == 0)
			return (ft_init_philo(data, &philo, i + 1), ft_routin(data, &philo),
				0);
		else
			i++;
	}
	ft_wait(data, 0, 0, 0);
	return (0);
}

int	main(int ac, char **ar)
{
	t_data	data;

	if (ft_init(&data, ac, ar, 0) == -1)
		return (ft_clean(&data), -1);
	ft_philo(&data, 0);
	return (ft_clean(&data), 0);
}
