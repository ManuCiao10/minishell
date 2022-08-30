/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 06:10:37 by hsaadi            #+#    #+#             */
/*   Updated: 2022/08/30 13:09:03 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strdup(const char *s)
{
	char	*tmp;

	if (!s)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (tmp == NULL)
		return (0);
	ft_strlcpy(tmp, s, sizeof(char) * (ft_strlen(s) + 1));
	*(tmp + ft_strlen(s)) = '\0';
	return (tmp);
}