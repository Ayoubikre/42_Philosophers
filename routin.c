/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:47:55 by noctis            #+#    #+#             */
/*   Updated: 2025/09/02 18:33:12 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ft_routin(void *ptr)
{
	t_philo *philo;
	
	philo= (t_philo *)ptr;
	
	printf("this is thread %d \n",philo->id);
	return (NULL);
}

void	*ft_monitor(void *ptr)
{
	t_data *data;
	
	data= (t_data *)ptr;
	
	printf("this is monitor and he is monitoring  %d of threds \n",data->nb);

	return (NULL);
}
