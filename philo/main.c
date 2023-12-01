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

/* usage: ./philo	
	<number_of_philosophers> 
	<time_to_die> 
	<time_to_eat> 
	<time_to_sleep> 
	[number_of_times_each_philosopher_must_eat]
*/
int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parse_args(&data, argc, argv))
		return (1);
	if (!init_data(&data))
		return (2);
	if (!philos_start(&data))
		return (clean_up(&data), 3);
	clean_up(&data);
	return (0);
}
