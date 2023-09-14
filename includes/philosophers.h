#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher	t_philo;

/*
args[0] = number_of_philosophers 
args[1] = time_to_die 
args[2] = time_to_eat
args[3] = time_to_sleep
args[4] = number_of_times_each_philosopher_must_eat
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
	int		idx;
	int		next_idx;
	int		eat_cnt;
	t_info	*info;
	struct timeval	last_eat;
}	t_philo;

/* init.c */
int		init_info(char **av, t_info *info);

/* dining.c */
void	*dining(void *arg);

/* util.c */
int		get_time(struct timeval start_time);
int		print_state(t_info *info, t_philo *p, char *str);

/* error.c */
int		arg_num_err(void);
int 	malloc_err(t_info *info, pthread_t *threads);
int		invaild_arg_err(void);

#endif