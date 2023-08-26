#include "philosophers.h"

int	main(int ac, char **av)
{
	t_info		info;
	pthread_t	*threads;
	int			i;

	if (ac < 5 || ac > 7)
		return (EXIT_FAILURE);
	if (init_info(av, &info) < 0)
		return (EXIT_FAILURE);
	threads = malloc(sizeof(pthread_t) * info.num_of_fork);
	i = 0;
	while (i < info.num_of_fork)
	{
		pthread_create(threads+i, NULL, simulation, &info);
		i++;
	}
	i = 0;
	while (i < info.num_of_fork)
	{
		pthread_join(threads+i, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
