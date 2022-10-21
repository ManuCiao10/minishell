#include "../include/minishell.h"

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
		printf("\033[0;0m");
}

int	strrlen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	even_(int n)
{
	if (n % 2 == 0)
		return (1);
	return (0);
}