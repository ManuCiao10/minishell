
#include "../include/minishell.h"


bool	init_shell(t_shell *shell, char **argv, char **envp)
{
	shell->argv = argv;
	shell->done = 0;
	if (!get_env(shell, envp))
		return (false);
	shell->prompt = NULL;
	shell->nb_cmd = 0;
	shell->size = 0;

	return (true);
}

