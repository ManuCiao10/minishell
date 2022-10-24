
#include "../include/minishell.h"

void	init_cmd(t_shell *shell)
{
	shell->cmd = malloc(sizeof(t_cmd));
	shell->cmd->command = ft_calloc(1, sizeof(char));
	shell->cmd->option = ft_calloc(1, sizeof(char));

}

bool	init_shell(t_shell *shell, char **argv, char **envp)
{
	shell->argv = argv;
	shell->done = 0;
	if (!get_env(shell, envp))
		return (false);
	init_cmd(shell);
	shell->prompt = NULL;
	shell->nb_cmd = 0;
	shell->size = 0;
	return (true);
}

