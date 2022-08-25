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

unsigned char *g;

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

void sig_handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	if(signum == SIGUSR1)
	{
		ft_printf("signal successfully recieved by the server\n");
		if(*++g)
		{
			ft_printf("global var value %c\n", *g);
			send_str_bits(info->si_pid, *g);
		}
		else
		{
			ft_printf("Nothing left to send\n");
			exit(EXIT_SUCCESS);
		}
	}
}

void	send_str_bits(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
		while (bit >= 0)
		{
			if ((c >> bit) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit--;
			usleep(100);
		}
}

int	main(int ac, char **av)
{
	struct sigaction sigact;

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
	sigact.sa_sigaction = sig_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	g = (unsigned char *)av[2];
	ft_printf("AV2 BEFORE ANY CALL %s\n", g);
	send_str_bits(ft_atoi(av[1]), *g);
	while(1)
		pause();
	return (0);
}
