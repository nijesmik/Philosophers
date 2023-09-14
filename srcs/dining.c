#include "philosophers.h"

void	take_time(struct timeval start_time, int time)
{
	int	remain;

	while (1)
	{
		remain = time - get_time(start_time);
		if (remain <= 0)
			return ;
		usleep(remain * 200);
	}
}

void	eat_sleep_think(t_philo *p, t_info *info)
{
	gettimeofday(&p->last_eat, NULL);
	print_state(info, p, "is eating");
	p->eat_cnt++;
	if (p->eat_cnt == info->args[4])
	{
		pthread_mutex_lock(&info->fin_mutex);
		if (info->fin < info->args[0])
			info->fin++;
		pthread_mutex_unlock(&info->fin_mutex);
	}
	take_time(p->last_eat, info->args[2]);
	pthread_mutex_unlock(&info->fork[p->next_idx]);
	pthread_mutex_unlock(&info->fork[p->idx]);
	print_state(info, p, "is sleeping");
	take_time(p->last_eat, info->args[2] + info->args[3]);
	print_state(info, p, "is thinking");
}

int	pick_fork(t_philo *p, t_info *info)
{
	pthread_mutex_lock(&info->fork[p->idx]);
	if (print_state(info, p, "has taken a left fork") < 0)
	{
		pthread_mutex_unlock(&info->fork[p->idx]);
		return (-1);
	}
	pthread_mutex_lock(&info->fork[p->next_idx]);
	if (print_state(info, p, "has taken a right fork") < 0)
	{
		pthread_mutex_unlock(&info->fork[p->idx]);
		pthread_mutex_unlock(&info->fork[p->next_idx]);
		return (-1);
	}
	return (0);
}

void	*simulation(void *arg)
{
	t_philo	*p;
	int		finish;

	p = (t_philo *)arg;
	gettimeofday(&p->last_eat, NULL);
	if (p->idx % 2 == 0)
		usleep(500 * p->info->args[2]);
	finish = 0;
	while (!finish)
	{
		if (pick_fork(p, p->info) < 0)
			return (NULL);
		eat_sleep_think(p, p->info);
		pthread_mutex_lock(&p->info->fin_mutex);
		if (p->info->fin == p->info->args[0])
			finish = 1;
		pthread_mutex_unlock(&p->info->fin_mutex);
	}
	return (NULL);
}

void	dining(t_info *info, t_malloc *m)
{
	int			i;

	i = info->args[0];
	gettimeofday(&info->start_time, NULL);
	while (i-- > 0)
	{
		m->philosophers[i].idx = i;
		m->philosophers[i].next_idx = (i + 1) % info->args[0];
		m->philosophers[i].eat_cnt = 0;
		m->philosophers[i].info = info;
		pthread_create(&m->threads[i], NULL, simulation, &m->philosophers[i]);
	}
	i = info->args[0];
	while (i-- > 0)
		pthread_join(m->threads[i], NULL);
	clear(info, m);
}
