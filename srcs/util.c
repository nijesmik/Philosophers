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

	msg = str;
	result = 0;
	pthread_mutex_lock(&p->info->fin_mutex);
	if (info->fin != info->args[0])
	{
		if (get_time(p->last_eat) > info->args[1])
		{
			msg = "died";
			result = -1;
			info->fin = info->args[0];
		}
		printf("%d %d %s\n", get_time(info->start_time), p->idx + 1, msg);
	}
	pthread_mutex_unlock(&p->info->fin_mutex);
	return (result);
}
