#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

size_t	ft_putstr(const char *str)
{
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

int32_t	ft_atoi(const char *str)
{
	int32_t	num;
	int		sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

