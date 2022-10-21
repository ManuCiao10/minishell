#include "../include/minishell.h"


bool	get_valid_cmd(t_shell *shell)
{
	int	index;

	index = 0;
	shell->cmd = ft_calloc(3, sizeof(t_cmd *));
	if (!shell->cmd)
		return (false);
	shell->nb_cmd = token_count(shell->buffer);
	//save the string in quotes
	//split the string with pipes
	return (true);
}


bool	parsing(t_shell *shell)
{
	// char	*dollar;
	// if (invalid_quotes(shell->prompt))
	// 	return (false);
	get_valid_cmd(shell);
	// dollar = dollar_sign(shell);
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
