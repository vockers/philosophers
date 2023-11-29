/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 12:20:45 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/28 12:20:45 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (get_time() - philo->ate_time > philo->data->time_to_die)
		return (1);
	return (0);
}

int	check_table(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		if (is_dead(&(data->philos[i])))
		{
			printf("%d %d has died\n", get_runtime(data->start_time), $(data->philos[i]));
			return (0);
		}
		i++;
	}
	return (1);
}

void monitor_philos(t_data *data)
{
	while (1)
	{
		if (!check_table(data))
			return ;
	}
}