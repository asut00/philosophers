/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:07:49 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/22 09:58:18 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_var	var;

	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	get_start_timestamp(&var);
	if (is_monophil(&var, argv))
		return (EXIT_SUCCESS);
	if (!init_all(&var, argc, argv))
		return (EXIT_FAILURE);
	wait_for_everyone_and_start(&var);
	wait_all_routines_ended_and_joined(&var);
	clean_before_exit(&var);
	return (EXIT_SUCCESS);
}
