#include "philosophers.h"

void	init_philo(t_info *info, t_philo *p, int idx)
{
	p->idx = idx;
	p->prev_idx = (idx - 1 + info->args[0]) % info->args[0];
	p->next_idx = (idx + 1) % info->args[0];
	p->eat_cnt = 0;
	p->info = info;
	p->state = THINK;
	info->fork[idx] = -1;
}

void	philosophers(t_info *info, t_philo *philosophers, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < info->args[0])
	{
		init_philo(info, &philosophers[i], i);
		pthread_create(&threads[i], NULL, simulation, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < info->args[0])
		pthread_join(threads[i++], NULL);
	free(info->fork);
	free(philosophers);
}

int	main(int ac, char **av)
{
	t_info		info;
	pthread_t	*threads;

	if (ac < 5 || ac > 7)
		return (arg_num_err());
	if (init_info(av, &info) < 0)
		return (EXIT_FAILURE);
	info.philosophers = malloc(sizeof(t_philo) * info.args[0]);
	if (!info.philosophers)
		return (malloc_err(NULL));
	threads = malloc(sizeof(pthread_t) * info.args[0]);
	if (!threads)
		return (malloc_err(info.philosophers));
	philosophers(&info, info.philosophers, threads);
	return (EXIT_SUCCESS);
}
