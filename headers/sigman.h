/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigman.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 01:23:36 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/27 10:49:14 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGMAN_H
# define SIGMAN_H
# include "server.h"

void	sig_manager(t_client *client, int hint, int *is_client);
#endif