#include "philosophers.h"

void	spend_time(struct timeval start_time, int time)
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

void	sleep_after_eat(t_philo *p, t_info *info)
{
	p->eat_cnt++;
	pthread_mutex_lock(&info->cnt_mutex);
	if (p->eat_cnt == info->args[4])
		info->cnt++;
	pthread_mutex_unlock(&info->cnt_mutex);
	spend_time(p->last_eat, info->args[2]);
	gettimeofday(&p->last_sleep, NULL);
	print_state(info, p->idx, "is sleeping");
	pthread_mutex_lock(&info->state_mutex);
	p->state = SLEEP;
	info->fork[p->idx] = -1;
	info->fork[p->next_idx] = -1;
	print_state(info, p->idx, "put down the forks");
	check_next_philosopher(p, info);
	pthread_mutex_unlock(&info->state_mutex);
}

void	think_after_sleep(t_philo *p, t_info *info)
{
	spend_time(p->last_sleep, info->args[3]);
	print_state(info, p->idx, "is thinking");
	pthread_mutex_lock(&info->state_mutex);
	p->state = THINK;
	pthread_mutex_unlock(&info->state_mutex);
}

int	is_finish(t_info *info)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&info->cnt_mutex);
	if (info->cnt == info->args[0])
		result = 1;
	pthread_mutex_unlock(&info->cnt_mutex);
	return (result);
}

void	*simulation(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	gettimeofday(&p->last_eat, NULL);
	if (p->idx % 2 == 0)
		usleep(100 * p->info->args[0]);
	while (1)
	{
		if (check_fork(p, p->info) < 0)
		{
			pthread_mutex_lock(&p->info->cnt_mutex);
			p->info->cnt++;
			pthread_mutex_unlock(&p->info->cnt_mutex);
			return (NULL);
		}
		sleep_after_eat(p, p->info);
		if (is_finish(p->info))
			return (NULL);
		think_after_sleep(p, p->info);
		if (is_finish(p->info))
			return (NULL);
	}
	return (NULL);
}
