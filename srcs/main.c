#include "philosophers.h"

int	main(int ac, char **av)
{
	t_info		info;
	t_malloc	m;

	if (ac < 5 || ac > 7)
	{
		write(2, "error : invalid number of arguments\n", 36);
		return (EXIT_FAILURE);
	}
	if (init(av, &info, &m) < 0)
		return (EXIT_FAILURE);
	dining(&info, &m);
	return (EXIT_SUCCESS);
}
