/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:50:03 by hsaadi            #+#    #+#             */
/*   Updated: 2022/08/30 12:32:57 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	unsigned long	i;
	if(!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
