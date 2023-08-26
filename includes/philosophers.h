#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_info
{
	int				num_of_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	mutex;
}	t_info;

typedef enum e_state {
	EATING,
	HUNGRY,
	THINKING,
}	t_state;

int		init_info(char **av, t_info *info);
void	*simulation(void *arg);

#endif