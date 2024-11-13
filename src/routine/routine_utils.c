/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:47:45 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 15:47:55 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_forks(t_fork **l_fork, t_fork **r_fork,
							long p_id, t_var *pvar)
{
	*r_fork = &pvar->forks[p_id - 1];
	if (p_id == pvar->num_of_phil)
		*l_fork = &pvar->forks[0];
	else
		*l_fork = &pvar->forks[p_id];
}

int	check_if_dead(t_var *pvar, t_philo *pphil)
{
	if (!get(&(pvar->var_mutex), &(pvar->deaths)))
		print_message(pphil, pvar, 's');
	else
	{
		set_increment(&pvar->var_mutex, &pvar->philo_routine_stopped);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	wait_all_routines_created(t_var *pvar)
{
	while (get(&pvar->var_mutex, &pvar->routines_started) < pvar->num_of_phil)
	{
		if (!get(&pvar->var_mutex, &pvar->program_is_running))
		{
			return (FAILURE);
		}
		usleep(1);
	}
	return (SUCCESS);
}
