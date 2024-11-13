/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:56:50 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/22 09:56:51 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

////////////////////////////////// HEADERS //////////////////////////////////

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>

////////////////////////////////// MACROS //////////////////////////////////

# define FALSE 0
# define TRUE 1

# define FAILURE 0
# define SUCCESS 1

////////////////////////////////// STRCT //////////////////////////////////

typedef struct s_fork
{
	long			id;
	pthread_mutex_t	mutex;
}			t_fork;

typedef struct s_philo
{
	long			id;
	long			time_to_die;
	long			dies_at;
	long			meals;
	long			full;

	t_fork			*forks;
	void			*var;

	struct timeval	last_meal;

	pthread_t		death_check_tid;

	pthread_mutex_t	phil_full_mutex;

}			t_philo;

typedef struct s_var
{
	t_philo			*philos;
	t_fork			*forks;

	long			num_of_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_num_of_meals;
	long			program_is_running;
	long			routines_started;
	long			threads_ready;
	long			death_threads_ready;
	long			all_threads_ready_go;

	long			deaths;
	long			death_checks_stopped;

	struct timeval	gtod_start_timestamp;
	long			start_timestamp_ms;

	long			full_phils;

	pthread_t		*routine_tids;
	long			philo_routine_stopped;
	pthread_t		gen_death_check_tid;

	pthread_mutex_t	print_mutex;

	pthread_mutex_t	var_mutex;
}		t_var;

typedef struct s_lrfs
{
	t_fork	*l_fork;
	t_fork	*r_fork;
}		t_lrfs;

////////////////////////////////// FCTS //////////////////////////////////

// check_args.c
int		arg_check(int argc, char **argv);
int		check_args(int argc, char **argv);

// philo_utils.c
int		ft_isdigit(int c);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
long	ft_atol(const char *str);

// init.c
int		init_all(t_var *pvar, int argc, char **argv);
int		init_gen_vars(t_var *pvar, char **argv, int argc);
int		init_forks_array(t_var *pvar);
int		init_routine_tids(t_var *pvar);
void	init_philo_forks(t_fork **l_fork,
			t_fork **r_fork, long p_id, t_var *pvar);

// start_program_handle_monophil.c
int		is_monophil(t_var *pvar, char **argv);
void	handle_mono_phil(long time_to_die, t_var *pvar);

// init_philos_array.c
int		init_philos_array(t_var *pvar);

// precise_usleep.c
long	get_elapsed_time_microseconds(struct timeval s, struct timeval e);
void	precise_usleep(long usec);

// get_timestamps.c
void	get_start_timestamp(t_var *pvar);
long	get_current_timestamp_ms(t_var *pvar);
long	get_full_current_timestamp_ms(void);

// clean_and_close.c
int		stop_program_sleep_and_return(t_var *pvar, int retvalue);
int		free_sleep_and_return(t_philo *pphilos, t_fork *pforks, int retvalue);
void	detach_previous_philo_routines(t_var *pvar, int i);
void	clean_before_exit(t_var *pvar);

// destroy.c
void	destroy_previous_forks_mutex(t_var *pvar, int i);
void	destroy_all_forks_mutex(t_var *pvar);
void	destroy_previous_phil_full_mutex(t_var *pvar, int i);
void	destroy_all_phil_full_mutex(t_var *pvar);

// destroy2.c
void	destroy_mutex_var_print(t_var *pvar);
void	destroy_mutex_var_print_forks_phils(t_var *pvar);

// death_check.c
int		create_and_detach_death_check(t_var *pvar);
void	*gen_death_check(void *data);

// getters.c
long	get(pthread_mutex_t *mutex, long *var);

// setters.c
void	set(pthread_mutex_t *mutex, long *dest, long value);
void	set_increment(pthread_mutex_t *mutex, long *dest);
int		set_increment_and_ret_zero(t_var *pvar, long *to_increment);
void	*set_increment_and_ret_null(t_var *pvar, long *to_increment);

// print_message.c
void	print_message(t_philo *pphil, t_var *pvar, char c);

// routine.c
void	*philo_routine(void *data);

// routine_utils.c
void	init_philo_forks(t_fork **l_fork, t_fork **r_fork,
			long p_id, t_var *pvar);
int		check_if_dead(t_var *pvar, t_philo *pphil);
int		wait_all_routines_created(t_var *pvar);

// wait.c
void	wait_all_threads_ready(t_var *pvar);
void	wait_all_death_threads_ready(t_var *pvar);
void	wait_for_everyone_and_start(t_var *pvar);
int		wait_for_the_go(t_var *pvar);
void	wait_all_routines_ended_and_joined(t_var *pvar);

// routine_eat.c
int		eat(t_philo *pphil, t_var *pvar, t_fork *l_fork, t_fork *r_fork);

#endif
