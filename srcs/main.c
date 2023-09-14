#include "philosophers.h"

static void	_clear(t_info *info, pthread_t *thread, t_philo *philo)
{
	int	i;

	i = info->args[0];
	while (i-- > 0)
		pthread_mutex_destroy(&info->fork[i]);
	pthread_mutex_destroy(&info->fin_mutex);
	free(info->fork);
	free(thread);
	free(philo);
}

void	init_philo(t_info *info, t_philo *p, int idx)
{
	p->idx = idx;
	p->next_idx = (idx + 1) % info->args[0];
	p->eat_cnt = 0;
	p->info = info;
	pthread_mutex_init(&info->fork[idx], NULL);
}

int	simulation(t_info *info)
{
	pthread_t	*threads;
	t_philo		*philosophers;
	int			i;

	threads = malloc(sizeof(pthread_t) * info->args[0]);
	if (!threads)
		return (malloc_err(info, NULL));
	philosophers = malloc(sizeof(t_philo) * info->args[0]);
	if (!philosophers)
		return (malloc_err(info, threads));
	i = info->args[0];
	gettimeofday(&info->start_time, NULL);
	while (i-- > 0)
	{
		init_philo(info, &philosophers[i], i);
		pthread_create(&threads[i], NULL, dining, &philosophers[i]);
	}
	i = info->args[0];
	while (i-- > 0)
		pthread_join(threads[i], NULL);
	_clear(info, threads, philosophers);
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;

	if (ac < 5 || ac > 7)
		return (arg_num_err());
	if (init_info(av, &info) < 0)
		return (EXIT_FAILURE);
	if (simulation(&info) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
