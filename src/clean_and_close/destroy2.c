/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:16:40 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 13:16:41 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_previous_forks_mutex(t_var *pvar, int i)
{
	while (i >= 1)
	{
		i--;
		pthread_mutex_destroy(&pvar->forks[i].mutex);
	}
}

void	destroy_all_forks_mutex(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_phil)
	{
		pthread_mutex_destroy(&pvar->forks[i].mutex);
		i++;
	}
}

void	destroy_previous_phil_full_mutex(t_var *pvar, int i)
{
	while (i >= 1)
	{
		i--;
		pthread_mutex_destroy(&pvar->philos[i].phil_full_mutex);
	}
}

void	destroy_all_phil_full_mutex(t_var *pvar)
{
	int	i;

	i = 0;
	while (i < pvar->num_of_phil)
	{
		pthread_mutex_destroy(&pvar->philos[i].phil_full_mutex);
		i++;
	}
}
