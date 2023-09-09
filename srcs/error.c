#include "philosophers.h"

int	arg_num_err(void)
{
	write(2, "error : invalid number of arguments\n", 36);
	return (EXIT_FAILURE);
}

int malloc_err(t_philo *philo)
{
	if (philo)
		free(philo);
	write(2, "memory allocation error\n", 24);
	return (EXIT_FAILURE);
}

int	invaild_arg_err(void)
{
	write(2, "error : 1 is invalid number of philosophers\n", 44);
	return (-1);
}