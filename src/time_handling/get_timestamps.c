/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:59:12 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/22 16:59:13 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_start_timestamp(t_var *pvar)
{
	gettimeofday(&(pvar->gtod_start_timestamp), NULL);
	pvar->start_timestamp_ms = (pvar->gtod_start_timestamp.tv_sec * 1000L)
		+ (pvar->gtod_start_timestamp.tv_usec / 1000L);
	pvar->program_is_running = TRUE;
}

long	get_current_timestamp_ms(t_var *pvar)
{
	struct timeval	current;
	long			current_timestamp_ms;

	gettimeofday(&current, NULL);
	current_timestamp_ms = ((current.tv_sec * 1000L)
			+ (current.tv_usec / 1000L)) - (pvar->start_timestamp_ms);
	return (current_timestamp_ms);
}

long	get_full_current_timestamp_ms(void)
{
	struct timeval	current;
	long			full_current_timestamp_ms;

	gettimeofday(&current, NULL);
	full_current_timestamp_ms = ((current.tv_sec * 1000L)
			+ (current.tv_usec / 1000L));
	return (full_current_timestamp_ms);
}
