#include "philosophers.h"

static size_t	_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

static int atoi_err(char *str)
{
	write(STDERR_FILENO, "error: ", 7); 
	write(STDERR_FILENO, str, _strlen(str));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	return (-1);
}

static int	_atoi(char *str)
{
	int		num;
	size_t	i;

	if (!str)
		return (0);
	if (!*str)
		return (atoi_err(str));
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			num = num * 10 + str[i++] - '0';
		else
			return (atoi_err(str));
	}
	return (num);
}

int	init_info(char **av, t_info *info)
{
	info->num_of_fork = _atoi(av[1]);
	if (info->num_of_fork < 0)
		return (-1);
	info->time_to_die = _atoi(av[2]);
	if (info->time_to_die < 0)
		return (-1);
	info->time_to_eat = _atoi(av[3]);
	if (info->time_to_eat < 0)
		return (-1);
	info->time_to_sleep = _atoi(av[4]);
	if (info->time_to_sleep < 0)
		return (-1);
	info->num_of_must_eat = _atoi(av[5]);
	if (info->num_of_must_eat < 0)
		return (-1);
	pthread_mutex_init(&info->mutex, NULL);
	return (0);
}
