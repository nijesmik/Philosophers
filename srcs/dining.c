#include "philosophers.h"

int	take_time(struct timeval start_time, int spend_time, t_info *info)
{
	int time;
	int	remain;
	
	time = get_time(start_time);
	while (time < spend_time)
	{
		if (info->args[1] < spend_time)
			remain = info->args[1] - time;
		else
			remain = spend_time - time;
		if (remain <= 0)
			remain = 1;
		usleep(remain * 200);
		pthread_mutex_lock(&info->fin_mutex);
		if (info->fin == info->args[0])
		{
			pthread_mutex_unlock(&info->fin_mutex);
			return (-1);
		}
		pthread_mutex_unlock(&info->fin_mutex);
		time = get_time(start_time);
	}
	return (0);
}

int	eat(t_philo *p, t_info *info)
{
	int result;

	pthread_mutex_lock(&p->eat_mutex);
	gettimeofday(&p->last_eat, NULL);
	p->eating = 1;
	pthread_mutex_unlock(&p->eat_mutex);
	result = print_state(info, p, "is eating");
	if (++(p->eat_cnt) == info->args[4])
	{
		pthread_mutex_lock(&info->fin_mutex);
		if (info->fin < info->args[0])
			info->fin++;
		pthread_mutex_unlock(&info->fin_mutex);
	}
	if (!result)
		result = take_time(p->last_eat, info->args[2], info);
	pthread_mutex_unlock(&info->fork[p->next_idx]);
	pthread_mutex_unlock(&info->fork[p->idx]);
	pthread_mutex_lock(&p->eat_mutex);
	p->eating = 0;
	pthread_mutex_unlock(&p->eat_mutex);
	return (result);
}

int	sleep_and_think(t_philo *p, t_info *info)
{
	if (print_state(info, p, "is sleeping") < 0)
		return (-1);
	if (take_time(p->last_eat, info->args[2] + info->args[3], info) < 0)
		return (-1);
	if (print_state(info, p, "is thinking") < 0)
		return (-1);
	return (0);
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

void	*dining(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	gettimeofday(&p->last_eat, NULL);
	if (p->idx % 2 == 1)
		usleep(250 * p->info->args[1]);
	while (1)
	{
		if (pick_fork(p, p->info) < 0)
			return (NULL);
		if (eat(p, p->info) < 0)
			return (NULL);
		if (sleep_and_think(p, p->info) < 0)
			return (NULL);
	}
	return (NULL);
}
