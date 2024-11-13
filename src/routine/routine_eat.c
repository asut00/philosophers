/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:53:40 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 15:53:49 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_new_dies_at(t_var *pvar, t_philo *pphil)
{
	pthread_mutex_lock(&pvar->var_mutex);
	pphil->dies_at = get_full_current_timestamp_ms() + pphil->time_to_die;
	pthread_mutex_unlock(&pvar->var_mutex);
}

int	odd_fork_picking(t_philo *pphil, t_var *pvar,
						t_fork *l_fork, t_fork *r_fork)
{
	if (pphil->meals == 0)
		usleep(1000);
	pthread_mutex_lock(&(l_fork->mutex));
	if (get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		pthread_mutex_unlock(&(l_fork->mutex));
		return (FAILURE);
	}
	print_message(pphil, pvar, 'l');
	pthread_mutex_lock(&(r_fork->mutex));
	if (get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		pthread_mutex_unlock(&(l_fork->mutex));
		pthread_mutex_unlock(&(r_fork->mutex));
		return (FAILURE);
	}
	print_message(pphil, pvar, 'r');
	return (SUCCESS);
}

int	even_fork_picking(t_philo *pphil, t_var *pvar,
						t_fork *l_fork, t_fork *r_fork)
{
	pthread_mutex_lock(&(r_fork->mutex));
	if (get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		pthread_mutex_unlock(&(r_fork->mutex));
		return (FAILURE);
	}
	print_message(pphil, pvar, 'r');
	pthread_mutex_lock(&(l_fork->mutex));
	if (get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		pthread_mutex_unlock(&(l_fork->mutex));
		pthread_mutex_unlock(&(r_fork->mutex));
		return (FAILURE);
	}
	print_message(pphil, pvar, 'l');
	return (SUCCESS);
}

int	eat_meal(t_philo *pphil, t_var *pvar, t_fork *l_fork, t_fork *r_fork)
{
	print_message(pphil, pvar, 'e');
	set_new_dies_at(pvar, pphil);
	precise_usleep(pvar->time_to_eat * 1000L);
	pthread_mutex_unlock(&(l_fork->mutex));
	pthread_mutex_unlock(&(r_fork->mutex));
	pphil->meals = pphil->meals + 1;
	if (pphil->meals == get(&pvar->var_mutex, &pvar->max_num_of_meals))
	{
		set(&pphil->phil_full_mutex, &pphil->full, 1);
		set_increment(&pvar->var_mutex, &pvar->full_phils);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	eat(t_philo *pphil, t_var *pvar, t_fork *l_fork, t_fork *r_fork)
{
	long	p_id;

	p_id = pphil->id;
	if (p_id % 2 == 1)
	{
		if (!odd_fork_picking(pphil, pvar, l_fork, r_fork))
			return (FAILURE);
	}
	else if (p_id % 2 == 0)
	{
		if (!even_fork_picking(pphil, pvar, l_fork, r_fork))
			return (FAILURE);
	}
	if (!eat_meal(pphil, pvar, l_fork, r_fork))
		return (FAILURE);
	return (SUCCESS);
}
