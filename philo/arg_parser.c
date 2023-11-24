#include "philo.h"

t_args	*parse_args(int argc, char *argv[])
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	if (argc != 5 && argc != 6)
	{
		ft_putstr("usage: ./philo <number_of_philosophers> " \
			"<time_to_die> <time_to_eat> <time_to_sleep>");
		return (NULL);
	}
	memset(args, 0, sizeof(t_args));
	args->philo_count = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->min_eat = ft_atoi(argv[5]);

	return (args);
}
