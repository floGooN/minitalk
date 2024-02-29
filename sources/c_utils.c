/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:42:58 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 12:06:47 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	sig_manager(int signum, int pid)
{
	if (signum <= 0)
	{
		if (signum == 0)
			write(2, "-- ERROR ARGUMENTS -- \n", 24);
		else if (signum == -1)
			write(2, "-- SIGACTION ERROR -- \n", 24);
		else if (signum == -2)
			ft_printf("-- SERVER %d NO RESPONDING --\n", pid);
		else
			write(2, "-- MEMORY ERROR --\n", 20);
		exit(EXIT_FAILURE);
	}
	ft_printf("\n-- SEND WITH SUCCESS -- (at %d)\n", pid);
	exit(EXIT_SUCCESS);
}

void	send_sig(int pid, int current_sig)
{
	if (kill(pid, current_sig) == -1)
		sig_manager(-2, 0);
}

static void	send_str(t_msg *message)
{
	static int	byte_pos;
	static int	index;

	if (((message->message[index] << byte_pos) & 0x80) == 0)
		message->curr_sig = SIGUSR1;
	else
		message->curr_sig = SIGUSR2;
	if (++byte_pos == 8)
	{
		byte_pos = 0;
		if (message->message[index])
			index++;
		else
			message->is_init = 3;
	}
	send_sig(message->pid_server, message->curr_sig);
}

static void	send_len(t_msg *message)
{
	static int	byte_pos;

	if (!byte_pos)
		message->size = ft_strlen((const char *) message->message);
	if (((message->size << byte_pos) & 0x80000000) == 0)
		message->curr_sig = SIGUSR1;
	else
		message->curr_sig = SIGUSR2;
	if (++byte_pos == 32)
		message->is_init = 2;
	send_sig(message->pid_server, message->curr_sig);
}

void	send_bit(t_msg *message, int retry)
{
	if (retry)
		send_sig(message->pid_server, message->curr_sig);
	else if (message->is_init == 1)
		send_len(message);
	else
		send_str(message);
}
