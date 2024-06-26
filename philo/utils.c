/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:11:58 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/27 13:11:58 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_runtime(long start_time)
{
	return ((int)(get_time() - start_time));
}

void	print_message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&(philo->data->print_lock));
	if (!is_dead(philo))
	{
		printf("%d %d %s\n", \
			get_runtime(philo->data->start_time), \
			philo->id, msg);
	}
	pthread_mutex_unlock(&(philo->data->print_lock));
}

void	ft_msleep(int msec)
{
	long	time;

	time = get_time();
	while (get_time() - time < msec)
		usleep(250);
}

int	ft_atoi(const char *str)
{
	long	res;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res > INT_MAX)
			return (-1);
		str++;
	}
	return ((int)res);
}
