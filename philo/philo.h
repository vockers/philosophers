#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct	s_args
{
	int32_t	philo_count;
	int32_t	time_to_die;
	int32_t	time_to_eat;
	int32_t	time_to_sleep;
	int32_t	min_eat;
}	t_args;

typedef struct	s_data
{
	t_args	*args;
}	t_data;

t_args	*parse_args(int argc, char *argv[]);

/* Utility functions */
size_t	ft_strlen(const char *str);
size_t	ft_putstr(const char *str);
int32_t	ft_atoi(const char *str);

#endif
