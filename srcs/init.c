#include "philosophers.h"

static size_t	_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

static int invalid_arg_err(char *str)
{
	write(STDERR_FILENO, "error: ", 7); 
	write(STDERR_FILENO, str, _strlen(str));
	write(STDERR_FILENO, ": is invalid argument\n", 22);
	return (-1);
}

static int	_atoi(char *str)
{
	long long	num;
	size_t		i;

	if (!str)
		return (0);
	if (!*str)
		return (invalid_arg_err(str));
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			num = num * 10 + str[i++] - '0';
		else
			return (invalid_arg_err(str));
		if (num > 2147483647)
			return (invalid_arg_err(str));
	}
	if (!num)
		return (invalid_arg_err(str));
	return (num);
}

static int	malloc_err(t_info *info, t_malloc *m)
{
	if (info->fork)
		free(info->fork);
	if (m->threads)
		free(m->threads);
	if (m->philosophers)
		free(m->philosophers);
	write(STDERR_FILENO, "memory allocation error\n", 24);
	return (-1);
}

int	init(char **av, t_info *info, t_malloc *m)
{
	int	i;

	i = 5;
	while (i-- > 0)
	{
		info->args[i] = _atoi(av[i + 1]);
		if (info->args[i] < 0)
			return (-1);
	}
	info->fork = malloc(sizeof(pthread_mutex_t) * info->args[0]);
	m->threads = malloc(sizeof(pthread_t) * info->args[0]);
	m->philosophers = malloc(sizeof(t_philo) * info->args[0]);
	if (!info->fork || !m->threads || !m->philosophers)
		return(malloc_err(info, m));
	i = info->args[0];
	while (i-- > 0)
		pthread_mutex_init(&info->fork[i], NULL);
	info->fin = 0;
	pthread_mutex_init(&info->fin_mutex, NULL);
	return (0);
}
