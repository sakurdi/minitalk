/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                    		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kurd <sal-kurd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:02:26 by sal-kurd          #+#    #+#             */
/*   Updated: 2022/08/16 18:46:50 by sal-kurd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_printf(char *s, ...);
void    send_str_bits(int pid);
#endif
