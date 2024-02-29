/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:54:02 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 11:56:37 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_client	*init_client(t_client *client, int pid_client)
{
	static t_client	*new_client = NULL;

	if (!new_client)
	{
		new_client = client;
		return (NULL);
	}
	else
	{
		if (kill(pid_client, 0) == -1)
			return (NULL);
		new_client->client_id = pid_client;
		new_client->init = 1;
		new_client->size = 0;
		new_client->index = 0;
		if (kill(pid_client, SIGUSR1) == -1)
			sig_manager(client, -2);
		return (new_client);
	}
}

static void	handler(int signum, siginfo_t *info, void *sec)
{
	static t_client	*client;
	static int		s_pid;

	(void) sec;
	if (!s_pid)
		s_pid = getpid();
	if (!client || !client->init)
		client = init_client(client, info->si_pid);
	else if (info->si_pid != client->client_id)
		return ;
	else
		fill_byte(client, signum);
	return ;
}

int	main(void)
{
	struct sigaction	act;
	t_client			server;

	init_client(&server, 0);
	if (init_sigaction(&act, handler) == -1)
		sig_manager(&server, -3);
	if (ft_printf("\n-- PROCESS ID : --- %d ---\n\n", getpid()) == -1)
		sig_manager(&server, -3);
	while (1)
	{
		pause();
		while (server.init)
		{
			if (sleep(3) == 0)
			{
				if (kill(server.client_id, SIGUSR1) == -1)
					sig_manager(&server, 1);
			}
		}
	}
	return (0);
}
