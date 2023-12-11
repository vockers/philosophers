/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/26 14:59:16 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/26 14:59:16 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(data->philo_count * sizeof(t_philo));
	if (philos == NULL)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].num_eaten = 0;
		philos[i].alive = true;
		if (i % 2 == 0)
		{
			philos[i].fork_r = &(data->forks[i]);
			philos[i].fork_l = &(data->forks[(i + 1) % data->philo_count]);
		}
		else
		{
			philos[i].fork_r = &(data->forks[(i + 1) % data->philo_count]);
			philos[i].fork_l = &(data->forks[i]);
		}
		if (pthread_mutex_init(&(philos[i].lock), NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&(philos[i].lock));
			return (free(philos), 0);
		}
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	return (1);
}

static int	init_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (forks == NULL)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&(forks[i]));
			return (free(forks), 0);
		}
		i++;
	}
	data->forks = forks;
	return (1);
}

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&(data->start_lock), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->print_lock), NULL) != 0)
		return (pthread_mutex_destroy(&(data->start_lock)), 0);
	if (!init_forks(data))
	{
		pthread_mutex_destroy(&(data->start_lock));
		pthread_mutex_destroy(&(data->print_lock));
		return (0);
	}
	if (!init_philos(data))
	{
		clean_up_forks(data->forks, data->philo_count);
		pthread_mutex_destroy(&(data->start_lock));
		pthread_mutex_destroy(&(data->print_lock));
		return (0);
	}
	return (1);
}
