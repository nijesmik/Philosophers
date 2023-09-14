#include "philosophers.h"

int	arg_num_err(void)
{
	write(2, "error : invalid number of arguments\n", 36);
	return (EXIT_FAILURE);
}

int malloc_err(t_info *info, pthread_t *threads)
{
	if (info->fork)
		free(info->fork);
	if (threads)
		free(threads);
	write(2, "memory allocation error\n", 24);
	return (-1);
}

int	invaild_arg_err(void)
{
	write(2, "error : 0 is invalid argument\n", 44);
	return (-1);
}