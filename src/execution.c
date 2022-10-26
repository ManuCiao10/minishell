#include "../include/minishell.h"

bool	run_process(t_shell *shell, int i)
{
	// char	*cmd;
    pid_t child;
    int pfd[2];
	// char	**opt;

	// cmd = get_cmd(shell->argv[i], shell->env);
	// opt = ft_split(shell->argv[i], ' ');
	if (pipe(pfd) == -1)
		msg_exit("Pipe creation failed!\n");
	child = fork();
	if (child == -1)
		msg_exit("Fork creation failed!\n");
	if (child == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		printf("shell->cmd[i].command[0] %s\n", shell->cmd[i].command[0]);
		printf("shell->cmd[i].command[1] %s\n", shell->cmd[i].command[1]);
		if (execve(shell->cmd[i].command[0], shell->cmd[i].command, shell->envp) == -1)
			msg_exit("Command execution failed}!\n");
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		waitpid(child, NULL, 0);
	}
	return (true);
}

void	run_parent(t_shell *shell)
{
	// char	*cmd;
	// char	**opt;
    int i = 0;
	// printf("shell->cmd[i].command[0] %s\n", shell->cmd[0].command[0]);
	// printf("shell->cmd[i].command[1] %s\n", shell->cmd[i].command[1]);
	while (i < shell->nb_cmd)
		run_process(shell, i++);
	// cmd = get_cmd(shell->argv[i], shell->env);
	// opt = ft_split(shell->argv[i], ' ');
	dup2(0, STDOUT_FILENO);
	if (execve(shell->cmd[i].command[0], shell->cmd[i].command, shell->envp) == -1)
			msg_exit("Command execution failed!\n");

}