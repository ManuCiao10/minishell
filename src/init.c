
#include "../include/minishell.h"

bool	init_shell(t_shell *shell, char **argv, char **envp)
{
	shell->argv = argv;
	shell->done = 0;
	if (!get_env(shell, envp))
		return (false);
	return (true);
}
