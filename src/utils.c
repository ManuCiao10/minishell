#include "../include/minishell.h"

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



