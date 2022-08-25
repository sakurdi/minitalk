/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                    		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kurd <sal-kurd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:06:47 by sal-kurd          #+#    #+#             */
/*   Updated: 2022/08/16 18:41:10 by sal-kurd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	c = 0;
	static pid_t			client_pid = 0;
	
	(void)context;
	if(!client_pid)
		client_pid = info->si_pid;
	ft_printf("recieved signal %d from %d\n", info->si_signo, client_pid);
	if (signum == SIGUSR1)
	{
		c = c | 1;
		kill(client_pid, SIGUSR1);
	}
	else
	{
		c = c | 0;
		kill(client_pid, SIGUSR1);
	}
	if (++bit == 8)
	{	
		bit = 0;
		client_pid = 0;
		ft_printf("8 bit representation -> %c\n", c);
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	int					pid;
	struct sigaction	sigact;

	pid = getpid();
	ft_printf("server PID -> %d\n", pid);
	sigact.sa_sigaction = sig_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
