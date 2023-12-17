#include "philosophers.h"

int	get_time(struct timeval start_time)
{
	struct timeval	cur_time;
	int				time;

	gettimeofday(&cur_time, NULL);
	time = (int)(cur_time.tv_sec - start_time.tv_sec) * 1000 \
			+ (cur_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

int	print_state(t_info *info, t_philo *p, char *str)
{
	char	*msg;
	int		result;

	result = -1;
	pthread_mutex_lock(&p->info->fin_mutex);
	if (info->fin < info->args[0])
	{
		result = 0;
		msg = str;
		if (!str)
		{
			msg = "died";
			info->fin = info->args[0];
		}
		printf("%d %d %s\n", get_time(info->start_time), p->idx + 1, msg);
	}
	pthread_mutex_unlock(&p->info->fin_mutex);
	return (result);
}

void	clear(t_info *info, t_malloc *m)
{
	int	i;

	i = info->args[0];
	while (i-- > 0)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&m->philosophers[i].eat_mutex);
	}
	pthread_mutex_destroy(&info->fin_mutex);
	free(info->fork);
	free(m->threads);
	free(m->philosophers);
}

void	monitoring(t_philo *philosophers, t_info *info)
{
	int finish;
	int	i;
	t_philo	*p;

	finish = 0;
	i = 0;
	usleep(500 * p->info->args[1]);
	while (!finish)
	{
		i = i % info->args[0];
		p = &philosophers[i];
		pthread_mutex_lock(&p->eat_mutex);
		if (!p->eating && get_time(p->last_eat) > info->args[1])
		{
			print_state(info, p, NULL);
			finish = 1;
			if (info->args[0] == 1)
				pthread_mutex_unlock(&info->fork[0]);	
		}
		pthread_mutex_unlock(&p->eat_mutex);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info		info;
	t_malloc	m;
	int			i;

	if (ac < 5 || ac > 7)
	{
		write(STDERR_FILENO, "error : invalid number of arguments\n", 36);
		return (EXIT_FAILURE);
	}
	if (malloc_and_init(av, &info, &m) < 0)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < info.args[0])
		pthread_create(&m.threads[i], NULL, dining, &m.philosophers[i]);
	monitoring(m.philosophers, &info);
	while (i-- > 0)
		pthread_join(m.threads[i], NULL);
	clear(&info, &m);
	return (EXIT_SUCCESS);
}
