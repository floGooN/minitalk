/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:39:46 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 12:06:52 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include "minitalk.h"

typedef struct s_msg
{
	int		pid_server;
	int		curr_sig;
	int		is_init;
	size_t	size;
	char	*message;
}	t_msg;

void	sig_manager(int signum, int pid);
void	send_sig(int pid, int current_sig);
void	send_bit(t_msg *message, int retry);
#endif