#include "philosophers.h"

int	pick_fork(t_philo *p, t_info *info)
{
	if (info->fork[p->idx] != p->prev_idx && info->fork[p->next_idx] != p->next_idx)
	{
		if (info->fork[p->idx] < 0)
		{
			info->fork[p->idx] = p->idx;
			print_state(info, p->idx, "has taken a left fork");
		}
		if (info->fork[p->next_idx] < 0)
		{
			info->fork[p->next_idx] = p->idx;
			print_state(info, p->idx, "has taken a right fork");
		}
		p->state = EAT;
		gettimeofday(&p->last_eat, NULL);
		print_state(info, p->idx, "is eating");
		return (1);
	}
	return (0);
}

int	is_thinking(t_philo *philo, t_info *info)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&info->state_mutex);
	if (philo->state == THINK)
		result = 1;
	pthread_mutex_unlock(&info->state_mutex);
	return (result);
}

int	check_state(t_philo *p, t_info *info)
{
	int		result;

	result = 1;
	pthread_mutex_lock(&info->state_mutex);
	if (p->state == THINK)
	{
		result = 0;
		if (get_time(p->last_eat) > info->args[1])
		{
			print_state(info, p->idx, "died");
			result = -1;
			p->state = DIE;
			if (info->fork[p->idx] == p->idx)
				info->fork[p->idx] = -1;
			else if (info->fork[p->next_idx] == p->idx)
				info->fork[p->next_idx] = -1;
		}
	}
	pthread_mutex_unlock(&info->state_mutex);
	return (result);
}

int	check_fork(t_philo *p, t_info *info)
{
	int	result;
	int	remain_time;
	
	while (is_thinking(p, info))
	{
		pthread_mutex_lock(&info->state_mutex);
		result = 1;
		if (p->state == THINK)
			result = pick_fork(p, info);
		pthread_mutex_unlock(&info->state_mutex);
		if (result)
			return (result);
		result = check_state(p, info);
		if (result)
			return (result);
		remain_time = info->args[1] - get_time(p->last_eat);
		usleep(remain_time * 100);
	}
	return (1);
}

void	check_next_philosopher(t_philo *p, t_info *info)
{	
	t_philo *left;
	t_philo *right;

	left = &info->philosophers[p->prev_idx];
	if (left->state == THINK)
	{
		info->fork[p->idx] = p->prev_idx;
		print_state(info, p->prev_idx, "has taken a right fork");
		pick_fork(left, info);	
	}
	right = &info->philosophers[p->next_idx];
	if (right->state == THINK)
	{
		info->fork[p->next_idx] = p->next_idx;
		print_state(info, p->next_idx, "has taken a left fork");
		pick_fork(right, info);	
	}
}
