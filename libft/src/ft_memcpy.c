/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:22:45 by fberthou          #+#    #+#             */
/*   Updated: 2024/02/26 04:47:36 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (!src || !dest)
		return (dest);
	while (n--)
	{
		*(char *)dest = *(const char *)src;
		dest ++;
		src ++;
	}
	return (tmp);
}
