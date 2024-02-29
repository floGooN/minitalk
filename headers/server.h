/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:11:27 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/29 10:35:06 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "minitalk.h"

typedef struct s_client
{
	int		client_id;
	int		init;
	size_t	size;
	size_t	index;
	char	*message;
}	t_client;

void	sig_manager(t_client *client, int hint);
void	fill_byte(t_client *client, int signum);
void	ft_reset(t_client *client);
#endif