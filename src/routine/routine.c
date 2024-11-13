/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:47:45 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 15:47:55 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_and_think(t_var *pvar, t_philo *pphil)
{
	long	t_think;

	precise_usleep(pvar->time_to_sleep * 1000L);
	if (!get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		print_message(pphil, pvar, 't');
		if (pvar->num_of_phil % 2 == 1)
		{
			t_think = ((pvar->time_to_eat - pvar->time_to_sleep))
				+ (0.01 * pvar->time_to_eat);
			if (pvar->time_to_eat
				+ pvar->time_to_sleep
				+ t_think >= pvar->time_to_die)
				t_think = 0;
			if ((pvar->time_to_eat * 2)
				+ pvar->time_to_sleep >= pvar->time_to_die)
				t_think = 0;
			precise_usleep((t_think * 1000L));
		}
	}
	else
		return (set_increment_and_ret_zero(pvar, &pvar->philo_routine_stopped));
	return (SUCCESS);
}

void	*routine_loop(t_var *pvar, t_philo *pphil, t_lrfs *plrfs)
{
	while (!get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		if (!get(&(pvar->var_mutex), &(pvar->deaths))
			&& eat(pphil, pvar, plrfs->l_fork, plrfs->r_fork))
		{
			if (!check_if_dead(pvar, pphil))
				return (NULL);
			if (!sleep_and_think(pvar, pphil))
				return (NULL);
		}
		else
			return (set_increment_and_ret_null(pvar,
					&pvar->philo_routine_stopped));
	}
	return (set_increment_and_ret_null(pvar, &pvar->philo_routine_stopped));
}

void	*philo_routine(void *data)
{
	t_philo	*pphil;
	t_var	*pvar;
	t_lrfs	lrfs;

	pphil = (t_philo *)data;
	pvar = (t_var *)pphil->var;
	if (!wait_all_routines_created(pvar))
	{
		set_increment(&pvar->var_mutex, &pvar->philo_routine_stopped);
		return (NULL);
	}
	init_philo_forks(&lrfs.l_fork, &lrfs.r_fork, pphil->id, pvar);
	set_increment(&pvar->var_mutex, &pvar->threads_ready);
	if (!wait_for_the_go(pvar))
		return (NULL);
	pphil->dies_at = get(&pvar->var_mutex,
			&pvar->start_timestamp_ms) + pvar->time_to_die;
	return (routine_loop(pvar, pphil, &lrfs));
}
