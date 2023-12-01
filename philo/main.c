/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:11:51 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/27 13:11:51 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo <number_of_philosophers> " \
			"<time_to_die> <time_to_eat> <time_to_sleep>");
		return (0);
	}
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_eat = ft_atoi(argv[5]);
	return (1);
}

// usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
int main(int argc, char *argv[])
{
	t_data	data;

	if (!parse_args(&data, argc, argv))
		return (1);
	if (!init_data(&data))
		return (2);
	if (!philos_start(&data))
		return (3);
	clean_up(&data);
	return (0);
}
