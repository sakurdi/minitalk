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
	if(!g)
	{
		ft_printf("Nothing left to do\n");
		exit(EXIT_SUCCESS);
	}
	if(signum == SIGUSR1)
	{
		ft_printf("signal successfully recieved by the server[%d]\n", info->si_pid);
		send_str_bits(info->si_pid);
	}
}

void	send_str_bits(int pid)
{
	static int	bit = 7;
	
	if(bit == -1)
	{
		g++;
		bit = 7;
	}
	if ((*g >> bit) & 1)
	{
		bit--;
    	kill(pid, SIGUSR1);
		return ;
	}
    else
	{	
		bit--;
    	kill(pid, SIGUSR2);
		return ;
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
	ft_printf("AV2 BEFORE ANY CALL %c\n", *g);
	send_str_bits(ft_atoi(av[1]));
	while(1)
		pause();
	return (0);
}
