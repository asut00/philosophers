/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:08:28 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/26 10:08:29 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads_ready(t_var *pvar)
{
	while (get(&(pvar->var_mutex), &(pvar->threads_ready)) < pvar->num_of_phil)
		usleep(100);
}

void	wait_all_death_threads_ready(t_var *pvar)
{
	while (get(&(pvar->var_mutex), &(pvar->death_threads_ready)) < 1)
		usleep(100);
}

void	wait_for_everyone_and_start(t_var *pvar)
{
	wait_all_death_threads_ready(pvar);
	wait_all_threads_ready(pvar);
	set(&pvar->var_mutex, &pvar->start_timestamp_ms,
		get_full_current_timestamp_ms());
	set(&pvar->var_mutex, &pvar->all_threads_ready_go, TRUE);
}

int	wait_for_the_go(t_var *pvar)
{
	while (!get(&pvar->var_mutex, &pvar->all_threads_ready_go))
	{
		if (!get(&pvar->var_mutex, &pvar->program_is_running))
			return (FAILURE);
		usleep(1);
	}
	return (SUCCESS);
}

void	wait_all_routines_ended_and_joined(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_phil)
	{
		pthread_join(pvar->routine_tids[i], NULL);
		i++;
	}
}
