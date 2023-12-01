/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 14:05:09 by vockers       #+#    #+#                 */
/*   Updated: 2023/12/01 14:05:09 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_up_philos(t_philo *philos, int num)
{
	int	i;

	if (philos == NULL)
		return ;
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&(philos[i].lock));
		i++;
	}
	free(philos);
}

void	clean_up_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	if (forks == NULL)
		return ;
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	free(forks);
}

void	clean_up(t_data *data)
{
	pthread_mutex_destroy(&(data->start_lock));
	pthread_mutex_destroy(&(data->print_lock));
	clean_up_philos(data->philos, data->philo_count);
	clean_up_forks(data->forks, data->philo_count);
}