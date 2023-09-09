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

void	print_state(t_info *info, int idx, char *str)
{
	printf("%d %d %s\n", get_time(info->start_time), idx + 1, str);
}
