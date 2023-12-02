/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 20:54:10 by vockers       #+#    #+#                 */
/*   Updated: 2023/12/01 20:54:10 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	valid_arg(char *arg)
{
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9'))
			return (false);
		arg++;
	}
	return (true);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep>");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!valid_arg(argv[i]))
		{
			printf("Error: argument is not a valid positive number\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (0);
	memset(data, 0, sizeof(t_data));
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count <= 0)
	{
		printf("Error: minimum number of philosophers must be 1\n");
		return (0);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_eat = ft_atoi(argv[5]);
	return (1);
}
