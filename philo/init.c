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

	i = 0;
	philos = malloc(data->philo_count * sizeof(t_philo));
	if (philos == NULL)
		return (0);
	while (i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].alive = true;
		philos[i].eating = false;
		philos[i].fork_r = &(data->forks[i]);
		philos[i].fork_l = &(data->forks[(i + 1) % data->philo_count]);
		pthread_mutex_init(&(philos[i].lock), NULL);
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

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (forks == NULL)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&(forks[i]));
			return (0);
		}
		i++;
	}
	data->forks = forks;
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	if (!init_forks(data))
		return (0);
	if (!init_philos(data))
		return (0);
	return (1);
}