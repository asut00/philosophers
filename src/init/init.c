/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:49:22 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 15:38:41 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_var *pvar, int argc, char **argv)
{
	if (!init_gen_vars(pvar, argv, argc))
		return (FAILURE);
	if (!init_forks_array(pvar))
		return (FAILURE);
	if (!init_philos_array(pvar))
		return (FAILURE);
	if (!create_and_detach_death_check(pvar))
		return (FAILURE);
	if (!init_routine_tids(pvar))
		return (FAILURE);
	return (SUCCESS);
}

int	init_gen_vars(t_var *pvar, char **argv, int argc)
{
	pvar->num_of_phil = ft_atol(argv[1]);
	pvar->time_to_die = ft_atol(argv[2]);
	pvar->time_to_eat = ft_atol(argv[3]);
	pvar->time_to_sleep = ft_atol(argv[4]);
	pvar->full_phils = 0;
	if (argc == 6)
		pvar->max_num_of_meals = ft_atol(argv[5]);
	else
		pvar->max_num_of_meals = -1;
	if (pthread_mutex_init(&(pvar->var_mutex), NULL))
		return (FAILURE);
	if (pthread_mutex_init(&(pvar->print_mutex), NULL))
	{
		pthread_mutex_destroy(&pvar->var_mutex);
		return (FAILURE);
	}
	pvar->deaths = 0;
	pvar->routines_started = 0;
	pvar->threads_ready = 0;
	pvar->death_threads_ready = FALSE;
	pvar->death_checks_stopped = FALSE;
	pvar->philo_routine_stopped = FALSE;
	pvar->all_threads_ready_go = FALSE;
	return (SUCCESS);
}

int	init_forks_array(t_var *pvar)
{
	long	i;

	pvar->forks = malloc(pvar->num_of_phil * sizeof(t_philo));
	if (pvar->forks == NULL)
	{
		pvar->program_is_running = FALSE;
		destroy_mutex_var_print(pvar);
		return (free_sleep_and_return(NULL, NULL, FAILURE));
	}
	i = 0;
	while (i < pvar->num_of_phil)
	{
		pvar->forks[i].id = i;
		if (pthread_mutex_init(&pvar->forks[i].mutex, NULL))
		{
			pvar->program_is_running = FALSE;
			destroy_previous_forks_mutex(pvar, i);
			destroy_mutex_var_print(pvar);
			return (free_sleep_and_return(NULL, pvar->forks, FAILURE));
		}
		i++;
	}
	return (SUCCESS);
}

int	handle_routine_thread_creation_fail(t_var *pvar, int i)
{
	set(&pvar->var_mutex, &pvar->program_is_running, FALSE);
	while (!get(&pvar->var_mutex, &pvar->death_checks_stopped))
		usleep(1000);
	while (i >= 1)
	{
		i--;
		pthread_join(pvar->routine_tids[i], NULL);
	}
	while (get(&pvar->var_mutex,
			&pvar->philo_routine_stopped) < i)
		usleep(1000);
	destroy_mutex_var_print_forks_phils(pvar);
	free(pvar->routine_tids);
	return (free_sleep_and_return(pvar->philos, pvar->forks, FAILURE));
}

int	init_routine_tids(t_var *pvar)
{
	int	i;

	pvar->routine_tids = malloc(pvar->num_of_phil * sizeof(pthread_t));
	if (!pvar->routine_tids)
	{
		set(&pvar->var_mutex, &pvar->program_is_running, FALSE);
		while (!get(&pvar->var_mutex, &pvar->death_checks_stopped))
			usleep(1000);
		destroy_mutex_var_print_forks_phils(pvar);
		return (free_sleep_and_return(pvar->philos, pvar->forks, FAILURE));
	}
	i = 0;
	while (i < pvar->num_of_phil)
	{
		if (pthread_create(&pvar->routine_tids[i], NULL,
				philo_routine, &pvar->philos[i]))
			return (handle_routine_thread_creation_fail(pvar, i));
		set_increment(&pvar->var_mutex, &pvar->routines_started);
		i++;
	}
	return (SUCCESS);
}
