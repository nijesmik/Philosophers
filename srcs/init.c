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
	int	i;

	i = 0;
	while (i < 5)
	{
		info->args[i] = _atoi(av[i + 1]);
		if (info->args[i] < 0)
			return (-1);
		else if (!info->args[i])
			return (invaild_arg_err());
		i++;
	}
	info->fork = malloc(sizeof(pthread_mutex_t) * info->args[0]);
	if (!info->fork)
		return(malloc_err(NULL, NULL));
	info->fin = 0;
	pthread_mutex_init(&info->fin_mutex, NULL);
	return (0);
}
