/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:25:49 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 12:25:50 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_program_sleep_and_return(t_var *pvar, int retvalue)
{
	pvar->program_is_running = FALSE;
	precise_usleep(1000000);
	return (retvalue);
}

int	free_sleep_and_return(t_philo *pphilos, t_fork *pforks, int retvalue)
{
	if (pphilos)
		free(pphilos);
	if (pforks)
		free(pforks);
	precise_usleep(1000000);
	ft_putstr_fd("Error: External function failure\n", 2);
	return (retvalue);
}

void	detach_previous_philo_routines(t_var *pvar, int i)
{
	while (i >= 1)
	{
		i--;
		pthread_detach(pvar->routine_tids[i]);
	}
}

void	clean_before_exit(t_var *pvar)
{
	pvar->program_is_running = FALSE;
	while (get(&pvar->var_mutex,
			&pvar->philo_routine_stopped) < pvar->num_of_phil)
		;
	while (get(&pvar->var_mutex, &pvar->death_checks_stopped) < 1)
		;
	destroy_all_forks_mutex(pvar);
	destroy_all_phil_full_mutex(pvar);
	pthread_mutex_destroy(&pvar->print_mutex);
	pthread_mutex_lock(&pvar->var_mutex);
	pthread_mutex_unlock(&pvar->var_mutex);
	pthread_mutex_destroy(&pvar->var_mutex);
	free(pvar->philos);
	free(pvar->forks);
	free(pvar->routine_tids);
}
