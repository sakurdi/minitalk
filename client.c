/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                    		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kurd <sal-kurd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:03:26 by sal-kurd          #+#    #+#             */
/*   Updated: 2022/08/16 18:49:00 by sal-kurd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *s)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	return (res * sign);
}

void	send_str_bits(int pid, char *s)
{
	int	bit;

	bit = 7;
	while (*s)
	{
		while (bit >= 0)
		{
			if ((*s >> bit) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit--;
			usleep(50);
		}
		s++;
		bit = 7;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("too few/too many arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (!av[2][0])
	{
		ft_printf("empty string argument\n");
		exit(EXIT_FAILURE);
	}
	send_str_bits(ft_atoi(av[1]), av[2]);
	return (0);
}
