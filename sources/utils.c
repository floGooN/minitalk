/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:31:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/23 03:16:14 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	init_sigaction(struct sigaction *act,
					void (handler)(int, siginfo_t *, void *))
{
	int	i;

	i = 1;
	act->sa_handler = NULL;
	act->sa_sigaction = handler;
	act->sa_flags = SA_SIGINFO;
	if (sigemptyset(&(act->sa_mask)) == -1)
		return (-1);
	while (i < 32)
	{
		if (i != SIGUSR1 && i != SIGUSR2)
		{
			if (sigaddset(&(act->sa_mask), i) == -1)
				return (-1);
		}
		i++;
	}
	if ((sigaction(SIGUSR1, act, NULL) == -1)
		|| (sigaction(SIGUSR2, act, NULL) == -1))
		return (-1);
	return (0);
}
