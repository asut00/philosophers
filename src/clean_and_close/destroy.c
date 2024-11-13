/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:16:40 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 13:16:41 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_var_print(t_var *pvar)
{
	pthread_mutex_destroy(&pvar->var_mutex);
	pthread_mutex_destroy(&pvar->print_mutex);
}

void	destroy_mutex_var_print_forks_phils(t_var *pvar)
{
	destroy_mutex_var_print(pvar);
	destroy_all_forks_mutex(pvar);
	destroy_all_phil_full_mutex(pvar);
}
