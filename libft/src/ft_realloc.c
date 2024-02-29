/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:01:42 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/23 02:37:23 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/libft.h"

void	*ft_realloc(void *pointer, size_t memory_size)
{
	void	*tmp;

	tmp = ft_calloc(memory_size, sizeof(char));
	if (!tmp)
		return (pointer);
	tmp = ft_memcpy(tmp, (const void *) pointer,
			ft_strlen((const char *)pointer));
	return (tmp);
}
