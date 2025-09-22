/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 01:57:43 by noctis            #+#    #+#             */
/*   Updated: 2025/09/22 16:50:58 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

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

int	ft_is_n_digit(int c)
{
	if ('0' <= c && c <= '9')
		return (0);
	return (1);
}

void	ft_close(t_data *data)
{
	sem_close(data->m_forks);
	sem_close(data->m_print);
	sem_close(data->m_dead);
	sem_close(data->m_meal_nb);
	if (data->pid)
		free(data->pid);
}

void	ft_unlink(void)
{
	sem_unlink("/m_forks");
	sem_unlink("/m_print");
	sem_unlink("/m_dead");
	sem_unlink("/m_meal_nb");
}

void	ft_clean(t_data *data)
{
	ft_close(data);
	ft_unlink();
}
