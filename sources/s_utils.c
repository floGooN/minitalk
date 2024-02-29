/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:06:42 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 11:59:29 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	print_str(t_client *client)
{
	if (client->message[0])
	{
		if (write(1, client->message, client->size) == -1)
			sig_manager(client, -1);
	}
	sig_manager(client, 777);
}

static void	get_size(t_client *client, int signum)
{
	static int	byte_pos;

	if (signum == SIGUSR1)
		client->size <<= 1;
	else if (signum == SIGUSR2)
	{
		client->size <<= 1;
		client->size |= 0x01;
	}
	if (++byte_pos == 32)
	{
		byte_pos = 0;
		client->message = ft_calloc(1, (client->size + 1));
		if (!client->message)
			sig_manager(client, -4);
		client->init = 2;
	}
}

static void	get_message(t_client *client, int signum)
{
	static int	byte_pos;

	if (signum == SIGUSR1)
		client->message[client->index] <<= 1;
	else if (signum == SIGUSR2)
	{
		client->message[client->index] <<= 1;
		client->message[client->index] |= 0x01;
	}
	if (++(byte_pos) == 8)
	{
		byte_pos = 0;
		if (client->message[client->index] == '\0')
		{
			print_str(client);
			return ;
		}
		client->index++;
	}
}

void	ft_reset(t_client *client)
{
	if (client)
	{
		if (client->message)
			free(client->message);
		client->client_id = 0;
		client->init = 0;
		client->size = 0;
		client->index = 0;
		client->message = NULL;
	}
}

void	fill_byte(t_client *client, int signum)
{
	if (client->init == 1)
		get_size(client, signum);
	else
		get_message(client, signum);
	if (client->init)
		if (kill(client->client_id, SIGUSR1) == -1)
			sig_manager(client, 1);
}
