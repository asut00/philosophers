/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:40:24 by asuteau           #+#    #+#             */
/*   Updated: 2024/08/22 16:40:25 by asuteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

long	ft_atol(const char *str)
{
	long	res;
	long	sign;
	long	sign_count;

	res = 0;
	sign = 1;
	sign_count = 0;
	while (*str && (*str == 32 || (9 <= *str && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = sign * -1;
		sign_count++;
		str++;
	}
	if (sign_count > 1)
		return (0);
	while (*str && '0' <= *str && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
