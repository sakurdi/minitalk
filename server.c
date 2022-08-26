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
	
	(void)context;
	if (signum == SIGUSR1)
		c = c | 1;
	else
		c = c | 0;
	if (++bit == 8)
	{	
		bit = 0;
		ft_printf("%c", c);
		c = 0;
	}
	else
		c <<= 1;
	kill(info->si_pid, SIGUSR1);
	return ;
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
