#include "../include/minishell.h"

bool	parsing(t_shell *shell)
{
	char	*dollar;

	if (!valid_quotes(shell))
		return (false);
	// get_valid_cmd(shell);
	dollar = dollar_sign(shell);
	// printf("%s \n", dollar);
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
		// print_env(shell.env);
		// printf("shell->size %d\n", shell.size);
		// printf("envp->size %d\n", strrlen(envp));
		prompting(&shell);
	}
	return (0);
}

// "ls|cat"