/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:58:33 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 12:00:23 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	unsuccess(t_client *client, int hint)
{
	if (hint == 666)
		write(1, "\n--- CRASH SERVER ---\n", 23);
	else if (hint == -1)
		write(1, "\n--- CRASH PRINTF ---\n", 23);
	else if (hint == -2)
		ft_printf("\n--- CRASH WRITE ---\n");
	else if (hint == -3)
		write (1, "\n-- LAUNCH ERROR  --\n", 22);
	else
		ft_printf("\n-- MEMORY ERROR FOR CLIENT %d --\n", client->client_id);
	write (1, "--- KILL SERVER ---\n", 22);
	kill(client->client_id, SIGUSR2);
	ft_reset(client);
}

static void	succes(t_client *client)
{
	if (client->message[0])
	{
		if (ft_printf("\n\n*** PRINT SUCCESS FROM %d ***\n", client->client_id)
			== -1)
			sig_manager(client, -1);
	}
	else
		if (ft_printf("\n*** EMPTY MESSAGE FROM %d ***\n", client->client_id)
			== -1)
			sig_manager(client, -1);
}

static void	no_responding(t_client *client)
{
	if (printf("## CLIENT %d NO RESPONDING ##\n", client->client_id) == -1)
		sig_manager(client, -1);
}

static void	reload(t_client *client)
{
	if (write (1, "--- SERVER RELOADED ---\n", 25) == -1)
		sig_manager(client, -2);
	if (ft_printf("\n-- PROCESS ID : --- %d ---\n\n", getpid()) == -1)
		sig_manager(client, -1);
	kill(client->client_id, SIGUSR2);
	ft_reset(client);
}

void	sig_manager(t_client *client, int hint)
{
	if (hint <= 0 || hint == 666)
	{
		unsuccess(client, hint);
		exit(EXIT_FAILURE);
	}
	else if (hint == 777)
		succes(client);
	else if (hint == 1)
		no_responding(client);
	else
	{
		ft_reset(client);
		return ;
	}
	reload(client);
}
