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
	int				*fork;
	int				cnt;
	struct timeval	start_time;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	cnt_mutex;
	t_philo			*philosophers;
}	t_info;

typedef enum e_state {
	THINK,
	EAT,
	SLEEP,
	DIE,
}	t_state;

typedef struct s_philosopher
{
	int		idx;
	int		prev_idx;
	int		next_idx;
	int		eat_cnt;
	t_info	*info;
	t_state	state;
	struct timeval	last_eat;
	struct timeval	last_sleep;
}	t_philo;

/* init.c */
int		init_info(char **av, t_info *info);

/* simulation.c */
void	*simulation(void *arg);

/* check.c */
int		check_fork(t_philo *philo, t_info *info);
void	check_next_philosopher(t_philo *p, t_info *info);

/* util.c */
int		get_time(struct timeval start_time);
void	print_state(t_info *info, int idx, char *str);

/* error.c */
int		arg_num_err(void);
int		malloc_err(t_philo *philo);
int		invaild_arg_err(void);

#endif