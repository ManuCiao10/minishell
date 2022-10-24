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

int	count_token(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
		i++;
	return (i);
}

void	print_struct(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmd)
	{
		printf("cmd[%d] = %s\n", i, shell->cmd[i].command);
		printf("option[%d] = %s\n", i, shell->cmd[i].option);
		i++;
	}
}