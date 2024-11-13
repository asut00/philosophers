/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:52:47 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 14:52:48 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	set_increment(pthread_mutex_t *mutex, long *dest)
{
	pthread_mutex_lock(mutex);
	*dest = *dest + 1;
	pthread_mutex_unlock(mutex);
}

int	set_increment_and_ret_zero(t_var *pvar, long *to_increment)
{
	set_increment(&pvar->var_mutex, to_increment);
	return (FAILURE);
}

void	*set_increment_and_ret_null(t_var *pvar, long *to_increment)
{
	set_increment(&pvar->var_mutex, to_increment);
	return (NULL);
}
