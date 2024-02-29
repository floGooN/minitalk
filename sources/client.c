/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:56:18 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 12:04:24 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	wake_up_server(int server_pid)
{
	write(1, "-- WE QUERY SERVER --", 22);
	if (kill(server_pid, SIGUSR1))
		sig_manager(-2, server_pid);
}

static t_msg	*init_client(t_msg *msg, int curr_pid)
{
	static t_msg	*new_message;

	if (!new_message)
	{
		new_message = msg;
		new_message->is_init = 0;
	}
	else if (curr_pid == new_message->pid_server)
	{
		new_message->is_init = 1;
		return (new_message);
	}
	return (NULL);
}

static void	init_struct(t_msg *message, int s_pid, char *msg)
{
	message->message = msg;
	message->pid_server = s_pid;
	if (!message->message || message->pid_server <= 0)
		sig_manager(0, 0);
	init_client(message, 0);
}

static void	handler(int signum, siginfo_t *info, void *sec)
{
	static t_msg	*message;

	(void) sec;
	if (!message)
	{
		message = init_client(message, info->si_pid);
		if (!message)
			return ;
	}
	if (info->si_pid != message->pid_server)
		return ;
	else if (signum == SIGUSR1)
		send_bit(message, 0);
	else if (signum == SIGUSR2 && message->is_init < 3)
		send_bit(message, 1);
	else
		sig_manager(777, message->pid_server);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	t_msg				message;

	ft_printf("-- MY CLIENT PID : %d --\n", getpid());
	if (argc != 3)
		sig_manager(0, 0);
	init_struct(&message, ft_atoi(argv[1]), argv[2]);
	if (init_sigaction(&act, &handler) == -1)
		sig_manager(-1, 0);
	send_sig(message.pid_server, SIGUSR1);
	while (1)
	{
		if (sleep(3) == 0)
		{
			if (message.is_init == 0)
				wake_up_server(message.pid_server);
			else
				if (kill(message.pid_server, 0) == -1)
					sig_manager(-2, message.pid_server);
		}
	}
	return (0);
}
