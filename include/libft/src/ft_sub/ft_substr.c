/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:01:39 by hsaadi            #+#    #+#             */
/*   Updated: 2022/10/29 13:44:49 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	if (len > l)
		len = l;
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	while (start < l && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
