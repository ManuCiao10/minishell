/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:30:47 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/29 13:44:49 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*srcs;

	if (!dst && !src)
		return (NULL);
	dest = (char unsigned *)dst;
	srcs = (char unsigned *)src;
	if (srcs < dest)
		while (len--)
			dest[len] = srcs[len];
	else
		while (len--)
			*dest++ = *srcs++;
	return (dst);
}
