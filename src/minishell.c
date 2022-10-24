#include "../include/minishell.h"

//assign value to the struct -->malloc struct

// void	print_shit(t_shell *shell)
// {

// }

char	*strtok_(char *str, char sepa)
{
	static char	*stock;
	char		*ptr;
	int			i;

	stock = NULL;
	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			ptr = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (ptr);
}

void	save_shit(char **string, t_shell *shell)
{
	int		i;

	i = 0;
	while (string[i])
	{
		shell->cmd[i].command = ft_calloc(sizeof(char *), 1);
		shell->cmd[i].option = ft_calloc(sizeof(char *), 1);
		shell->cmd->command = strtok_(string[i], ' ');
		printf("cmd: %s\n", shell->cmd[i].command);
		while (shell->cmd->command != NULL)
		{
			shell->cmd->command = strtok_(NULL, ' ');
			printf("options: %s\n", shell->cmd[i].command);
			break ;
		}
		i++;
	}
}

bool	get_valid_cmd(t_shell *shell)
{
	char	**buff;

	buff = ft_split(shell->prompt, '|');
	save_shit(buff, shell);
	// print_shit(shell);
	return (true);
}

bool	parsing(t_shell *shell)
{
	get_valid_cmd(shell);
	return (true);
}

void	prompting(t_shell *shell)
{
	while (!shell->done)
	{
		shell->prompt = readline("\033[0;36m\033[1m$minishell ▸ \033[0m");
		add_history(shell->prompt);
		parsing(shell);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	if (argc == 1)
	{
		if (!init_shell(&shell, argv, envp))
			return (false);
		prompting(&shell);
	}
	return (0);
}
