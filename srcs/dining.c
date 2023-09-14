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
	usleep(info->args[1] * 200);
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

int	is_fin(t_info *info)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&info->fin_mutex);
	if (info->fin == info->args[0])
		result = 1;
	pthread_mutex_unlock(&info->fin_mutex);
	return (result);
}

void	*dining(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	gettimeofday(&p->last_eat, NULL);
	if (p->idx % 2 == 0)
		usleep(500 * p->info->args[2]);
	while (1)
	{
		if (pick_fork(p, p->info) < 0)
			return (NULL);
		eat_sleep_think(p, p->info);
		if (is_fin(p->info))
			return (NULL);
	}
	return (NULL);
}
