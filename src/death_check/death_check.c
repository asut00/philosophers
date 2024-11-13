/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:43:32 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 14:43:33 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_and_detach_death_check(t_var *pvar)
{
	if (pthread_create(&pvar->gen_death_check_tid, NULL, gen_death_check, pvar))
	{
		pvar->program_is_running = FALSE;
		destroy_all_forks_mutex(pvar);
		destroy_all_phil_full_mutex(pvar);
		destroy_mutex_var_print(pvar);
		return (free_sleep_and_return(pvar->philos, pvar->forks, FAILURE));
	}
	if (pthread_detach(pvar->gen_death_check_tid))
	{
		set(&pvar->var_mutex, &pvar->program_is_running, FALSE);
		pthread_join(pvar->gen_death_check_tid, NULL);
		destroy_all_forks_mutex(pvar);
		destroy_all_phil_full_mutex(pvar);
		destroy_mutex_var_print(pvar);
		return (free_sleep_and_return(pvar->philos, pvar->forks, FAILURE));
	}
	return (SUCCESS);
}

int	init_death_check(t_var *pvar, t_philo	**pphil, int *i)
{
	*i = 0;
	*pphil = &(pvar->philos)[*i];
	set_increment(&pvar->var_mutex, &pvar->death_threads_ready);
	while (!get(&pvar->var_mutex, &pvar->all_threads_ready_go))
	{
		if (!get(&pvar->var_mutex, &pvar->program_is_running))
		{
			set_increment(&pvar->var_mutex, &pvar->death_checks_stopped);
			return (FAILURE);
		}
		usleep(1);
	}
	return (SUCCESS);
}

int	get_time_and_check_if_dead(t_var *pvar, t_philo *pphil)
{
	long	full_current_timestamp_ms;

	full_current_timestamp_ms = get_full_current_timestamp_ms();
	if (full_current_timestamp_ms >= get(&pvar->var_mutex, &pphil->dies_at)
		&& !get(&pvar->var_mutex, &pvar->deaths))
	{
		set(&(pvar->var_mutex), &(pvar->deaths), 1);
		print_message(pphil, pvar, 'd');
		set_increment(&pvar->var_mutex, &pvar->death_checks_stopped);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	*gen_death_check(void *data)
{
	t_var	*pvar;
	t_philo	*pphil;
	int		i;

	pvar = (t_var *)data;
	if (!init_death_check(pvar, &pphil, &i))
		return (NULL);
	while (i <= pvar->num_of_phil && !get(&pvar->var_mutex, &pvar->deaths)
		&& !get(&pphil->phil_full_mutex, &pphil->full))
	{
		if (!get_time_and_check_if_dead(pvar, pphil))
			return (NULL);
		i++;
		if (i == pvar->num_of_phil)
			i = 0;
		pphil = &(pvar->philos)[i];
		usleep(100);
	}
	set_increment(&pvar->var_mutex, &pvar->death_checks_stopped);
	return (NULL);
}
