#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

/**
* args[0] = number_of_philosophers 
* args[1] = time_to_die 
* args[2] = time_to_eat
* args[3] = time_to_sleep
* args[4] = number_of_times_each_philosopher_must_eat
*/
typedef struct s_info
{
	int				args[5];
	int				fin;
	struct timeval	start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	fin_mutex;
}	t_info;

typedef struct s_philosopher
{
	int				idx;
	int				next_idx;
	int				eat_cnt;
	t_info			*info;
	pthread_mutex_t	eat_mutex;
	char			eating;
	struct timeval	last_eat;
}	t_philo;

typedef struct s_malloc
{
	pthread_t	*threads;
	t_philo		*philosophers;	
}	t_malloc;

/* init.c */
int		malloc_and_init(char **av, t_info *info, t_malloc *m);

/* dining.c */
void	*dining(void *arg);

/* util (main.c) */
int		get_time(struct timeval start_time);
int		print_state(t_info *info, t_philo *p, char *str);

#endif