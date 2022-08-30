/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsaadi <hsaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:25:42 by hsaadi            #+#    #+#             */
/*   Updated: 2022/04/25 15:54:28 by hsaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*box;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		box = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = box;
	}
	*lst = NULL;
}
