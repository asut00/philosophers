/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:37:54 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/22 16:37:55 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_and_retzero(char *to_print)
{
	ft_putstr_fd(to_print, 2);
	return (FAILURE);
}

int	check_benchmark_limits(char **argv)
{
	if (ft_atol(argv[1]) > 200)
		return (put_and_retzero("Error: too many philosophers\n"));
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
		return (put_and_retzero("Error: argument error\n"));
	return (SUCCESS);
}

int	number_is_correct(int arg, char **argv, int i)
{
	if (arg > 2147483647)
		return (put_and_retzero("Error: arg must be between 0 and int max\n"));
	if (arg <= 0)
		return (put_and_retzero("Error: arg must be between 0 and int max\n"));
	if (argv[i][0] == '-')
		return (put_and_retzero("Error: argument starts by '-'\n"));
	return (SUCCESS);
}

int	arg_check(int argc, char **argv)
{
	int	i;
	int	j;
	int	arg;

	if (!check_benchmark_limits(argv))
		return (FAILURE);
	i = 1;
	while (i < argc)
	{
		arg = ft_atol(argv[i]);
		if (!number_is_correct(arg, argv, i))
			return (FAILURE);
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (put_and_retzero("Error: argument is not a number\n"));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: argument error, argc must be 5 or 6\n");
		return (FALSE);
	}
	if (!arg_check(argc, argv))
		return (FALSE);
	return (TRUE);
}
