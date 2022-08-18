/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:53:30 by hsaadi            #+#    #+#             */
/*   Updated: 2022/04/25 07:41:15 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s10;
	unsigned char	*s20;

	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	while ((*s10 || *s20) && n--)
		if (*s10++ != *s20++)
			return (*(--s10) - *(--s20));
	return (0);
}
