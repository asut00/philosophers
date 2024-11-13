/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:05:01 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 15:05:02 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *pphil, t_var *pvar, char c)
{
	long	p_id;

	p_id = pphil->id;
	pthread_mutex_lock(&pvar->print_mutex);
	if (c == 'd')
		printf("%ld %ld died\n", get_current_timestamp_ms(pvar), pphil->id);
	if (!get(&(pvar->var_mutex), &(pvar->deaths)))
	{
		if (c == 'l')
			printf("%ld %ld has taken a fork\n",
				get_current_timestamp_ms(pvar), p_id);
		else if (c == 'r')
			printf("%ld %ld has taken a fork\n",
				get_current_timestamp_ms(pvar), p_id);
		else if (c == 'e')
			printf("%ld %ld is eating\n",
				get_current_timestamp_ms(pvar), p_id);
		else if (c == 's')
			printf("%ld %ld is sleeping\n",
				get_current_timestamp_ms(pvar), p_id);
		else if (c == 't')
			printf("%ld %ld is thinking\n",
				get_current_timestamp_ms(pvar), p_id);
	}
	pthread_mutex_unlock(&pvar->print_mutex);
}
