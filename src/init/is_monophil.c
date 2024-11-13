/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_monophil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:38:46 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/23 15:38:49 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_monophil(t_var *pvar, char **argv)
{
	if (argv[1][0] == '1' && ft_strlen(argv[1]) == 1)
	{
		handle_mono_phil(ft_atol(argv[2]), pvar);
		return (TRUE);
	}
	return (FALSE);
}

void	handle_mono_phil(long time_to_die, t_var *pvar)
{
	precise_usleep(time_to_die * 1000L);
	printf("%ld %d died\n", get_current_timestamp_ms(pvar), 1);
}
