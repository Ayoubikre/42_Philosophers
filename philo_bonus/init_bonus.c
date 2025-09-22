/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 01:25:14 by noctis            #+#    #+#             */
/*   Updated: 2025/09/22 16:51:03 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_check(int ac, char **ar)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (ar[i][j])
		{
			if (ft_is_n_digit(ar[i][j]))
				return (-1);
			j++;
		}
		if (ft_atoi(ar[i]) <= 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_init_sem(t_data *data)
{
	ft_unlink();
	data->m_forks = sem_open("/m_forks", O_CREAT | O_EXCL, 0644, data->nb);
	data->m_print = sem_open("/m_print", O_CREAT | O_EXCL, 0644, 1);
	data->m_dead = sem_open("/m_dead", O_CREAT | O_EXCL, 0644, 1);
	data->m_meal_nb = sem_open("/m_meal_nb", O_CREAT | O_EXCL, 0644, 1);
	if (data->m_forks == SEM_FAILED || data->m_print == SEM_FAILED
		|| data->m_dead == SEM_FAILED || data->m_meal_nb == SEM_FAILED)
		return (-1);
	return (0);
}

void	ft_init_philo(t_data *data, t_philo *philo, int id)
{
	data->philo = philo;
	philo->id = id;
	philo->meal_nb = 0;
	philo->last_meal_time = data->start_time;
}

int	ft_init(t_data *data, int ac, char **ar)
{
	data->pid = NULL;
	data->philo = NULL;
	if (ac < 5 || ac > 6 || ft_check(ac, ar) == -1)
		return (printf(RED "ERROR : Invalid Arguments\n" RESET), -1);
	data->nb = ft_atoi(ar[1]);
	data->tt_die = ft_atoi(ar[2]);
	data->tt_eat = ft_atoi(ar[3]);
	data->tt_sleep = ft_atoi(ar[4]);
	data->meal_max = -1;
	if (ac == 6)
		data->meal_max = ft_atoi(ar[5]);
	data->start_time = get_timestamp();
	data->dead = 0;
	if (ft_init_sem(data) == -1)
		return (-1);
	data->pid = malloc(sizeof(pid_t) * data->nb);
	if (!data->pid)
		return (-1);
	memset(data->pid, 0, sizeof(data->pid) * data->nb);
	return (0);
}
