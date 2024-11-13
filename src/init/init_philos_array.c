/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:13:50 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/22 19:13:51 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_unit_vars(t_var *pvar, int i)
{
	pvar->philos[i].id = i + 1;
	gettimeofday(&(pvar->philos[i].last_meal), NULL);
	pvar->philos[i].time_to_die = pvar->time_to_die;
	pvar->philos[i].dies_at = ((pvar->philos[i].last_meal.tv_sec * 1000L)
			+ (pvar->philos[i].last_meal.tv_usec / 1000L))
		+ (pvar->time_to_die);
	pvar->philos[i].forks = pvar->forks;
	pvar->philos[i].var = (t_var *)pvar;
	pvar->philos[i].meals = 0;
	pvar->philos[i].full = 0;
}

int	init_philos_array(t_var *pvar)
{
	long	i;

	pvar->philos = malloc(pvar->num_of_phil * sizeof(t_philo));
	if (!pvar->philos)
	{
		pvar->program_is_running = FALSE;
		destroy_all_forks_mutex(pvar);
		destroy_mutex_var_print(pvar);
		return (free_sleep_and_return(NULL, pvar->forks, FAILURE));
	}
	i = 0;
	while (i < pvar->num_of_phil)
	{
		init_philo_unit_vars(pvar, i);
		if (pthread_mutex_init(&pvar->philos[i].phil_full_mutex, NULL))
		{
			pvar->program_is_running = FALSE;
			destroy_all_forks_mutex(pvar);
			destroy_previous_phil_full_mutex(pvar, i);
			destroy_mutex_var_print(pvar);
			return (free_sleep_and_return(pvar->philos, pvar->forks, FAILURE));
		}
		i++;
	}
	return (SUCCESS);
}
