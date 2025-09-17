/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 09:04:26 by noctis            #+#    #+#             */
/*   Updated: 2025/09/17 20:24:40 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void *ft_log(t_data *data, int id, char*msg)
{
    pthread_mutex_lock(&data->m_print);
        if(data->dead)
            return NULL;
        printf("%lld %d %s", get_timestamp() - data->start_time, philo->id.)
    
}

void	*ft_routin_one(void *ptr)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)ptr;
    data = philo->data;

    
}
void	*ft_routin(void *ptr)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)ptr;
    data = philo->data;
    
    if(philo->id % 2==0)
        ft_sleep(data->tt_sleep*1000);
        


}


void	*ft_monitor(void *arg)
{
    t_data *data;

    data = (t_data *)arg;

    

}