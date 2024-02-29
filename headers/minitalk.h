/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:42:57 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/27 11:03:23 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>

int	init_sigaction(struct sigaction *act, void (h)(int, siginfo_t *, void *));
#endif