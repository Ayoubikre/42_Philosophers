/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:05:21 by aakritah          #+#    #+#             */
/*   Updated: 2025/09/20 02:18:32 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	ft_philo(t_data *data, int i)
{
}

int	main(int ac, char **ar)
{
	t_data	data;

	if (ft_init(&data, ac, ar, 0) == -1)
		return (ft_clean(&data), -1);
	ft_philo(&data, 0);
	return (ft_clean(&data), 0);
}
