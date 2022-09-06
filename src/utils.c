/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:26:09 by eardingh          #+#    #+#             */
/*   Updated: 2022/09/06 09:31:36 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_only(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

//1=red 2=green 3=yellow 4=blue 5=purple 6=cyan 7=white 
void	ft_color(int color)
{
	if (color == 1)
		printf("\033[1;31m");
	else if (color == 2)
		printf("\033[1;32m");
	else if (color == 3)
		printf("\033[1;33m");
	else if (color == 4)
		printf("\033[1;34m");
	else if (color == 5)
		printf("\033[1;35m");
	else if (color == 6)
		printf("\033[1;36m");
	else if (color == 7)
		printf("\033[1;37m");
	else if (color == 8)
		printf("\033[0m");
}

char	*ft_remove_char(char *token, char sep)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == sep)
		{
			j = i;
			while (token[j])
			{
				token[j] = token[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (token);
}

char	*ft_strjoin_2(char *s1, char const *s2, int f)
{
	char	*tmp;
	int		is;
	int		id;

	is = 0;
	id = 0;
	if (!s1 || !s2)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tmp == NULL)
		return (NULL);
	while (s1 && s1[is])
	{
		tmp[is] = s1[is];
		is++;
	}
	while (s2 && s2[id])
		tmp[is++] = s2[id++];
	tmp[is] = '\0';
	if (f == 1)
		free(s1);
	return (tmp);
}